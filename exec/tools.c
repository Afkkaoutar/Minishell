/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:03:41 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/13 05:10:37 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_files(t_args *args, char *filename, int flag)
{
	int	err;

	err = 0;
	if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK) == -1)
			err = 1;
	}
	if (flag == INPUT && access(filename, F_OK) == -1)
		err = 2;
	if (err == 2)
		return (put_error(args, INTROUVABLE_FILE, filename), 1);
	else if (err == 1)
		return (put_error(args, PERMISSION, filename), 1);
	return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
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


char *path(t_env *env, const char *var_name)
{
    t_env *current = env;
    size_t var_len = ft_strlen(var_name);

    while (current)
    {
        char *env_var = current->value;
        if (ft_strncmp(env_var, var_name, var_len) == 0 && env_var[var_len] == '=')
        {
            return (env_var + var_len + 1);
        }
        current = current->next;
	}
    return NULL;
}

void add_to_env_list(t_env **env, const char *var_name, const char *var_value)
{
    t_env *current = *env;
    t_env *new_node = NULL;

    while (current != NULL)
    {
        if (ft_strcmp(current->var, var_name) == 0)
        {
            free(current->value);
            current->value = ft_strdup(var_value);
            return;
        }
        current = current->next;
    }

    new_node = malloc(sizeof(t_env));
    if (!new_node)
    {
        perror("malloc");
        return;
    }
    
    new_node->var = ft_strdup(var_name);
    new_node->value = ft_strdup(var_value);
    new_node->next = *env;
    *env = new_node;
}
