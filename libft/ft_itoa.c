/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 00:38:59 by kaafkhar          #+#    #+#             */
/*   Updated: 2023/12/26 19:48:39 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_lenght(long int nb)
{
	int	lenght;

	lenght = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		lenght = 1;
	while (nb)
	{
		nb = nb / 10;
		lenght++;
	}
	return (lenght);
}

char	*ft_itoa(int n)
{
	int			lenght;
	char		*str;
	long		nb;

	nb = n;
	lenght = ft_count_lenght(nb);
	str = (char *)malloc(lenght + 1);
	if (!str)
		return (NULL);
	str[lenght] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		str[lenght - 1] = nb % 10 + 48;
		nb = nb / 10;
		lenght--;
	}
	return (str);
}
