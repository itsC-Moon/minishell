/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:44:40 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/12 13:10:43 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

static int ft_strl(char *s)
{
	int i;

	i = 0;
	while (s != NULL && s[i] != 0)
		i++;
	return (i);
}

char    *ft_strdup(char *s1)
{
    char    *dup;
    int        i;

    i = 0;
    dup = malloc(sizeof(char) * (ft_strl(s1) + 1));
	check_null(dup, "malloc");
    while (*s1)
        dup[i++] = *s1++;
    dup[i] = '\0';
    return (dup);
}
