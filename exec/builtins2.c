/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/13 05:47:28 by kaafkhar         ###   ########.fr       */
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

void delete_node(t_env **head, const char *key)
{
    t_env *current = *head;
    t_env *prev = NULL;

    if (current != NULL && strcmp(current->var, key) == 0)
    {
        *head = current->next;
        free(current->var);
        free(current->value);
        free(current);
        printf("La variable \"%s\" a été supprimée de l'environnement.\n", key);
        return;
    }
    while (current != NULL && strcmp(current->var, key) != 0)
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Node with key \"%s\" not found in the list.\n", key);
        return;
    }
    prev->next = current->next;
    free(current->var);
    free(current->value);
    free(current);
    printf("La variable \"%s\" a été supprimée de l'environnement.\n", key);
}

void exec_unset(t_env **env, const char *var_name)
{
    if (var_name == NULL)
        return;
    printf("Tentative de suppression de la variable: %s\n", var_name);
    delete_node(env, var_name);
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

        add_to_env_list(env, var_name, var_value);

        *equal_sign = '=';
        i++;
    }
}
