/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 03:45:57 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/26 04:05:46 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_args *arg, char **cmd)
{
	char	*cwd;

	(void)arg;
	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		g_errno = 1;
		return (g_errno);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	g_errno = 0;
	return (g_errno);
}

void	exec_exit(t_args *args, t_cmd_tab *cmd)
{
	(void)args;
	if (cmd->arg && cmd->arg[0])
	{
		if (cmd->next)
		{
			printf("exit\nSHELL: exit: too many arguments\n");
			g_errno = 1;
		}
		else if (is_num(cmd->arg))
		{
			printf("exit\n");
			g_errno = ft_atoi(cmd->arg);
			exit(g_errno);
		}
		else
		{
			printf("exit\nSHELL: exit: %s: numeric argument required\n",
				cmd->arg);
			g_errno = 255;
			exit(g_errno);
		}
	}
	exit(g_errno);
}

void	exec_env(t_cmd_tab *cmd, t_list *env)
{
	t_list	*tmp;

	if (cmd->arg && ft_strcmp(cmd->arg, "|") != 0)
	{
		printf("env: %s: No such file or directory\n", cmd->arg);
		g_errno = 127;
		return ;
	}
	tmp = env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	g_errno = 0;
}

static void	remove_env_var(t_args *args, char *cmd)
{
	char		*env_var;
	t_list		*prev;
	t_list		*current;

	prev = NULL;
	current = args->env;
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, cmd, ft_strlen(cmd)) == 0
			&& env_var[ft_strlen(cmd)] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				args->env = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_args *args, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		remove_env_var(args, cmd[i]);
		i++;
	}
	g_errno = 0;
	return (0);
}
