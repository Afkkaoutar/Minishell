/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exuc_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:11:48 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/20 21:13:44 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_builtin(t_args *args, t_cmd_tab *cmd)
{
    printf("test :: %s\n", cmd->cmd[0]);
    
    if (ft_strcmp(cmd->cmd[0], "echo") == 0)
        exec_echo(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
        exec_cd(cmd, args->env);
    else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
        ft_pwd(args, cmd->cmd);
    else if (ft_strcmp(cmd->cmd[0], "export") == 0)
        ft_export(args, cmd->cmd);
    else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
        exec_exit(args, cmd);
    else if (ft_strcmp(cmd->cmd[0], "env") == 0)
        exec_env(cmd, args->env);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
 