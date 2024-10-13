/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:34:46 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/13 02:44:56 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>' );
}

char *ft_strndup(const char *s1, size_t n)
{
    char *copy ;
    
    copy = malloc(n + 1);
    if (!copy)
        return NULL;

    ft_strlcpy(copy, (char *)s1, n + 1);
    return copy;
}


void environment(char **env, t_args *cmd_line) 
{
    t_env *current = NULL;
    int i = 0;

    while (env[i] != NULL) 
    {
        t_env *new_env = malloc(sizeof(t_env));
        if (!new_env)
            exit(1);

        char *eq_pos = ft_strchr(env[i], '=');
        if (eq_pos) {
            size_t name_len = eq_pos - env[i];

            new_env->var = ft_strndup(env[i], name_len);
            new_env->value = ft_strdup(eq_pos + 1);
            new_env->next = NULL;

            if (!current) {
                cmd_line->env = new_env;
            } else {
                current->next = new_env;
            }

            current = new_env;
        }
        i++;
    }
    if (current) {
        current->next = NULL;
    }
}