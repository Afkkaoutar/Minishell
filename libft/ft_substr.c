/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 22:38:30 by kaafkhar          #+#    #+#             */
/*   Updated: 2023/12/19 21:47:50 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	ns;
	char	*p;	

	i = 0;
	if (!s)
		return (NULL);
	ns = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ns)
		return (ft_strdup(""));
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (*s && i < len)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	return (p[i] = '\0', p);
}
