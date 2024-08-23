/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:50:32 by kaafkhar          #+#    #+#             */
/*   Updated: 2023/12/19 21:47:27 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	int	i;
	int	j;

	if (!set || !s)
		return (NULL);
	j = ft_strlen(s) - 1;
	i = 0;
	if (j == -1)
		return (ft_substr(s, 0, 0));
	while (s[i])
	{
		if (!ft_strchr(set, s[i]))
			break ;
		i++;
	}
	while (j)
	{
		if (!ft_strchr(set, s[j]))
			break ;
		j--;
	}
	return (ft_substr(s, i, j - i + 1));
}
