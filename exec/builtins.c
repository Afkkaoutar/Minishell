/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/09 19:17:33 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo(t_args *args, t_cmd_tab *cmd)
{
    (void)args;

    int newline = 1;
    int i = 0;

    if (cmd && !cmd->cmd[1])
    {
        printf("\n");
        return;
    }

    if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    while (cmd->cmd[++i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
    }

    if (newline)
        printf("\n");
}

int cd(t_cmd_tab *cmd, t_env *env)
{
    if (cmd->arg)
    {
        if (chdir(cmd->arg) != 0)
            perror("cd");
    }
    else
    {
        if (chdir(path(env, "HOME")) != 0)
            perror("cd");
    }
    return 1;
}

int pwd(t_args *arg, char **cmd)
{
    (void)arg;
    (void)cmd;

    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        return 0;
    }
    printf("%s\n", cwd);
    free(cwd);
    return 1; 
}

void exec_exit(t_args *args, t_cmd_tab *cmd)
{
    (void)args;

    if (cmd->arg && cmd->arg[0])
    {
        if (cmd->next)
        {
            fprintf(stderr, "exit: too many arguments\n");
            return;
        }
        if (is_num(cmd->arg))
        {
            exit(ft_atoi(cmd->arg));
        }
        else
        {
            fprintf(stderr, "exit: %s: numeric argument required\n", cmd->arg);
            exit(255);
        }
    }
    exit(0);
}

void exec_env(t_cmd_tab *cmd, t_env *env)
{
    (void)cmd;

    if (!env)
        return;

    t_env *tmp = env;
    while (tmp)
    {
        if (tmp->var && tmp->value)
        {
            printf("%s=%s\n", tmp->var, tmp->value);
        }
        tmp = tmp->next;
    }
}
