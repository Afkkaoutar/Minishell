/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:36:15 by ychagri           #+#    #+#             */
/*   Updated: 2024/09/21 00:40:17 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_array(char **str)
{
    int i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void free_tokens(t_token **lst)
{
    t_token *tmp;

    if (!lst || !*lst)
        return;

    while (*lst)
    {
        tmp = *lst;
        *lst = tmp->next;
        if (tmp->content)
            free(tmp->content);
        free(tmp);
    }
}

void del(void *content)
{
    if (content)
    {
        t_env *env_var = (t_env *)content;
        free(env_var->var);
        free(env_var->value);
        free(env_var);
    }
}

void free_table(t_cmd_tab **table)
{
    t_cmd_tab *tmp;

    if (!table || !*table)
        return;

    while (*table)
    {
        tmp = *table;
        *table = tmp->next;
        if (tmp->arg)
            free(tmp->arg);
        if (tmp->cmd)
            free_array(tmp->cmd);
        if (tmp->delimiter)
            ft_lstclear(&tmp->delimiter, del);
        if (tmp->in)
            free(tmp->in);
        if (tmp->out)
            free(tmp->out);
        if (tmp->append)
            free(tmp->append);
        free(tmp);
    }
}

void free_struct(t_args *cmd_line)
{
    if (!cmd_line)
        return;

    if (cmd_line->line)
        free(cmd_line->line);
    if (cmd_line->tokens)
        free_tokens(&cmd_line->tokens);
    if (cmd_line->env)
        ft_lstclear(&cmd_line->env, del);
    if (cmd_line->path)
        free_array(cmd_line->path);
    if (cmd_line->table)
        free_table(&cmd_line->table);
    free(cmd_line);
}
