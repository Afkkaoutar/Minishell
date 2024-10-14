/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 05:36:15 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/14 05:10:17 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void del_env(void *content)
{
    t_env *env = (t_env *)content;
    if (env)
    {
        free(env->var);
        free(env->value);
        free(env);
    }
}

void free_list(t_list **list)
{
    t_list *temp;
    while (*list)
    {
        temp = *list;
        *list = (*list)->next;

        if (temp->content)      
             del_env(temp->content);

        free(temp);
    }
}


void free_delimiters(t_lim **lst)
{
    t_lim *tmp;

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
        if (tmp->in)
            free(tmp->in);
        if (tmp->out)
            free(tmp->out);
        if (tmp->append)
            free(tmp->append);
        if (tmp->delimiter)
            free_delimiters(&tmp->delimiter);
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
        free_list((t_list **)&cmd_line->env);
    if (cmd_line->path)
        free_array(cmd_line->path);
    if (cmd_line->table)
        free_table(&cmd_line->table);
    ft_bzero(cmd_line, sizeof(t_args));
}
