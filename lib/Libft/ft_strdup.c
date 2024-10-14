/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:37:36 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/14 04:11:46 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *str)
{
    char *dup;
    size_t i;

    if (!str) // Vérifier si la chaîne d'origine est nulle
        return (0);
    dup = malloc(ft_strlen(str) + 1); // Allocation de mémoire
    if (!dup)
        return (0);
    i = 0;
    while (str[i]) { // Accès à str[i]
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0'; // Terminaison de la chaîne
    return (dup);
}
