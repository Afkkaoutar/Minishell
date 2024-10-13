/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:11:48 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/13 22:46:18 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_builtin(t_args *args, t_cmd_tab *cmd)
{

    // printf("test :: %s\n", cmd->cmd[0]);
    if (ft_strcmp(cmd->cmd[0], "echo") == 0)
        echo(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
        exec_cd(cmd, args->env);
    else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
        pwd(args, cmd->cmd);
    else if (ft_strcmp(cmd->cmd[0], "export") == 0)
        ft_export(args, cmd->cmd, &args->env);
    else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
        exec_exit(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "env") == 0)
        exec_env(cmd, args->env);
    else if (ft_strcmp(cmd->cmd[0], "unset") == 0) 
    {
        if (cmd->cmd[1]) 
            exec_unset(&args->env, cmd->cmd[1]);
    }
    else 
        return (0); 
    return (1);
}
