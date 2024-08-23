/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:28:03 by kaafkhar          #+#    #+#             */
/*   Updated: 2023/12/22 19:17:54 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*a;
	char	*k;

	i = 0;
	a = (char *)haystack;
	k = (char *)needle;
	if (!*k)
		return (a);
	while (a[i] && i <= len)
	{
		j = 0;
		while (a[i + j] == k[j] && i + j < len && k[j])
			j++;
		if (k[j] == '\0')
			return (a + i);
		i++;
	}
	return (NULL);
}
