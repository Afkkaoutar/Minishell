/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:29:58 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/10/26 02:19:08 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_equal_position(char *cmd)
{
	char	*append_pos;
	int		i;

	i = 0;
	append_pos = ft_strnstr(cmd, "+=", ft_strlen(cmd));
	if (append_pos)
		return (append_pos - cmd);
	while (cmd[i] != '=' && cmd[i])
		i++;
	return (i);
}

t_list	*find_env_node(t_list *env, char *cmd)
{
	char	*env_var;
	char	*env_equal;
	int		i;
	t_list	*current;

	i = get_equal_position(cmd);
	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		env_equal = ft_strchr(env_var, '=');
		if (env_equal && (ft_strncmp(env_var, cmd, i) == 0)
			&& ((size_t)(env_equal - env_var) == (size_t)i))
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_list	*find_env_node2(t_list *env, char *cmd)
{
	char		*env_var;
	int			i;
	t_list		*current;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
		i++;
	current = env;
	while (current)
	{
		env_var = (char *)current->content;
		if ((ft_strncmp(env_var, cmd, i)) == 0 && env_var[i] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}
