/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 00:25:13 by kaafkhar          #+#    #+#             */
/*   Updated: 2023/12/22 10:15:50 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ak;

	if ((int)count < 0 && (int)size < 0)
		return (NULL);
	ak = (void *) malloc(count * size);
	if (!ak)
		return (NULL);
	ft_bzero(ak, count * size);
	return (ak);
}
