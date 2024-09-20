/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:01:15 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/21 00:38:40 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_echo(t_args *args, t_cmd_tab *cmd)
{
    (void)args;
    bool new_line = true;
    int i = 0;

    if (cmd && !cmd->cmd[1])
    {
        printf("\n");
        return;
    }
    if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n") == 0)
    {
        new_line = false;
        i++;
    }
    while (cmd->cmd[++i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
    }
    if (new_line)
        printf("\n");
}

int exec_cd(t_cmd_tab *cmd, t_list *env)
{
    if (cmd->arg)
    {
        if (chdir(cmd->arg) != 0)
            perror("cd");
    }
    else
    {
        if (chdir(get_path(env, "HOME")) != 0)
            perror("cd");
    }
    return 1;
}

int ft_pwd(t_args *arg, char **cmd)
{
    (void)arg;
    (void)cmd;
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("pwd");
        return (0);
    }
    ft_putendl_fd(cwd, 1);
    free(cwd);
    return (1); 
}

void exec_exit(t_args *args, t_cmd_tab *cmd)
{
    (void)args;
    if (cmd->arg && cmd->arg[0])
    {
        if (cmd->next)
            printf("exit\nSHELL: exit: too many arguments\n");
        else if (is_num(cmd->arg))
        {
            printf("exit\n");
            exit(ft_atoi(cmd->arg));
        }
        else
        {
            printf("exit\nSHELL: exit: %s: numeric argument required\n", cmd->arg);
            exit(255);
        }
    }
    exit(0);
}

void exec_env(t_cmd_tab *cmd, t_list *env)
{
    if (cmd->arg && ft_strcmp(cmd->arg, "|") != 0)
    {
        printf("env: %s: No such file or directory\n", cmd->arg);
        return;
    }

    t_list *tmp = env;
    while (tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}

int ft_export(t_args *arg, char **cmd)
{
    (void)arg;
    int i = 1;

    while (cmd[i])
    {
        char *equal_sign = ft_strchr(cmd[i], '=');
        if (equal_sign == NULL || equal_sign == cmd[i])
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return (0);
        }

        *equal_sign = '\0'; 
        const char *name = cmd[i];
        const char *value = equal_sign + 1; 

        *equal_sign = '='; 

        if (setenv(name, value, 1) == -1)
        {
            perror("setenv");
            return (0); 
        }
        i++;
    }
    return (1);
}

void exec_unset(t_token *tokens, t_list **env)
{
    if (tokens->next)
        tokens = tokens->next;
    else
        return;

    while (tokens)
    {
        if (check_is_env((char *)tokens->content, *env)) 
            delete_node(env, (char *)tokens->content);
        tokens = tokens->next;
    }
}


int own_strchr(char *str, char n)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == n)
            return (1);
        i++;
    }
    return (0);
}

int is_num(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

bool get_flag(t_args *global, char *cmd)
{
    t_token *cur = global->tokens;
    while (cur)
    {
        if (ft_strcmp((char *)cur->content, cmd) == 0 && cur->next
            && cur->next->type == FLAG)
        {
            if (own_strchr((char *)cur->next->content, 'n'))
                return (1);
        }
        cur = cur->next;
    }
    return (0);
}

char *get_path(t_list *env, const char *var_name)
{
    t_list *current = env;
    size_t var_len = ft_strlen(var_name);

    while (current)
    {
        char *env_var = (char *)current->content;
        if (ft_strncmp(env_var, var_name, var_len) == 0 && env_var[var_len] == '=')
        {
            return (env_var + var_len + 1);
        }
        current = current->next;
    }
    return NULL;
}

int check_is_env(char *enve, t_list *env)
{
    while (env)
    {
        t_env *env_var = (t_env *)env->content;
        if (ft_strcmp(enve, env_var->var) == 0)
            return (1);
        env = env->next;
    }
    return (0);
}

void delete_node(t_list **head, const char *key)
{
    t_list *current = *head;
    t_list *prev = NULL;

    while (current != NULL)
    {
        t_env *env_var = (t_env *)current->content;
        if (ft_strcmp(env_var->var, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;

            del(current->content);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Node with key \"%s\" not found in the list.\n", key);
}
