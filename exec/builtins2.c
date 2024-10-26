/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:04:49 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/26 04:08:03 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ordre_alpha(t_list **env)
{
		t_list *i;
		t_list *j;
		char *temp;

		if (!env || !(*env))
			return;

		i = *env;
		while (i)
		{
			j = i->next;
			while (j)
			{
				if (ft_strcmp((char *)i->content, (char *)j->content) > 0)
				{
					temp = i->content;
					i->content = j->content;
					j->content = temp;
				}
				j = j->next;
			}
			i = i->next;
	}
}

static int	append_env_value(t_list *env_node, char *cmd, char *equal_sign)
{
	char		*old_value;
	char		*new_value;
	char		*temp;
	char		*final;

	old_value = ft_strchr((char *)env_node->content, '=');
	if (!old_value)
		return (1);
	old_value++;

	new_value = ft_strjoin(old_value, equal_sign + 1);
	if (!new_value)
		return (1);
	temp = ft_strjoin(cmd, "=");
	if (!temp)
	{
		free(new_value);
		return (1);
	}
	final = ft_strjoin(temp, new_value);
	free(temp);
	free(new_value);

	if (!final)
		return (1);

	free(env_node->content);
	env_node->content = final;
	return (0);
}

int	update_env_value(t_list *env_node, char *cmd, int append)
{
	char	*key;
	char	*equal_sign;
	char	*append_pos;

	append_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
	equal_sign = append ? (append_pos + 1) : ft_strchr(cmd, '=');

	if (!equal_sign)
		return (1);

	key = ft_substr(cmd, 0, append ? (append_pos - cmd) : (equal_sign - cmd));
	if (!key)
		return (1);

	if (append)
	{
		if (append_env_value(env_node, cmd, equal_sign))
		{
			free(key);
			return (1);
		}
	}
	else
	{
		free(env_node->content);
		env_node->content = ft_strdup(cmd);
		if (!env_node->content)
		{
			free(key);
			return (1);
		}
	}

	free(key);
	return (0);
}
int is_valid_identifier(const char *str)
{
    if (!str || !*str)
        return (0);

    if (!isalpha(*str) && *str != '_')
        return 0;

    str++;
    while (*str)
    {
        if (!isalnum(*str) && *str != '_')
            return 0;
        str++;
    }
    return (1);
}

int export_variable(t_args *args, t_cmd_tab *cmd)
{
    t_list *current;

    if (cmd->cmd[1] == NULL)
    {
        current = args->env;
        while (current)
        {
            printf("declare -x %s\n", (char *)current->content);
            current = current->next;
        }
        return (0);
    }

    char *append_sign = ft_strnstr(cmd->cmd[1], "+=", ft_strlen(cmd->cmd[1]));
    char *equal_sign = append_sign ? append_sign + 1 : ft_strchr(cmd->cmd[1], '=');

    if (!equal_sign && !append_sign)
    {
        printf("export: invalid argument: %s\n", cmd->cmd[1]);
        return (1);
    }

    char *identifier;
    if (append_sign)
        identifier = ft_substr(cmd->cmd[1], 0, append_sign - cmd->cmd[1]);
    else
        identifier = ft_substr(cmd->cmd[1], 0, equal_sign - cmd->cmd[1]);

    if (!is_valid_identifier(identifier))
    {
        printf("export: `%s': not a valid identifier\n", cmd->cmd[1]);
        free(identifier);
        return (1);
    }
    free(identifier);

    t_list *env_node = find_env_node(args->env, cmd->cmd[1]);
    if (env_node)
    {
        return update_env_value(env_node, cmd->cmd[1], append_sign != NULL);
    }
    else
    {
        char *new_content;
        if (append_sign)
        {
            char *key = ft_substr(cmd->cmd[1], 0, append_sign - cmd->cmd[1]);
            if (!key)
                return (1);
            
            char *value = ft_strjoin("=", equal_sign + 1);
            if (!value)
            {
                free(key);
                return (1);
            }
            
            new_content = ft_strjoin(key, value);
            free(key);
            free(value);
        }
        else
            new_content = ft_strdup(cmd->cmd[1]);

        if (!new_content)
            return (1);

        t_list *new_node = ft_lstnew(new_content);
        if (!new_node)
        {
            free(new_content);
            return (1);
        }

        ft_lstadd_back(&(args->env), new_node);
    }

    ordre_alpha(&(args->env));
    return (0);
}