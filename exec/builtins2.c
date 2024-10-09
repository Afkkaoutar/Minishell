/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/08 18:05:30 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int own_strchr(char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return i;
        i++;
    }
    return -1;
}

void exec_unset(t_env **env, const char *var_name)
{
    t_env *prev = NULL;
    t_env *current = *env;

    while (current)
    {
        if (ft_strcmp(current->var, var_name) == 0)
        {
            if (prev == NULL)
            {
                *env = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current->var);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}


void ft_export(t_args *args, char **cmd, t_env **env)
{
    (void)args;
    int i = 1;
    int j = 0;

    if (cmd[1] == NULL) 
    {
        extern char **environ; 
        while (environ[j] != NULL)
        {
            char *equal_sign = ft_strchr(environ[j], '=');
            if (equal_sign)
            {
                *equal_sign = '\0';
                printf("declare -x %s=\"%s\"\n", environ[j], equal_sign + 1);
                *equal_sign = '=';
            }
            else
            {
                printf("declare -x %s\n", environ[j]);
            }
            j++;
        }
        return;
    }

    while (cmd[i])
    {
        char *equal_sign = ft_strchr(cmd[i], '=');
        if (equal_sign == NULL)
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return;
        }

        *equal_sign = '\0';
        const char *var_name = cmd[i];
        const char *var_value = equal_sign + 1;

        if (setenv(var_name, var_value, 1) == -1)
        {
            perror("setenv");
            return; 
        }

        *equal_sign = '=';
        add_to_env_list(env, var_name, var_value);
        i++;
    }
}
