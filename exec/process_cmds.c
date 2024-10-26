/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:10:03 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/26 01:30:16 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cmds(t_args *args)
{
    t_cmd_tab *table;

    table = args->table;
    if (!table)
        return (0);
    if (table && table->next == NULL)
    {
        if (exec_builtin(args, table) == 0)
            return (1);
        if (single_cmd(table) == -1)
            return (1);
    }
    else if (exec_pipes(table))
        return (1);
    return (0);
}
