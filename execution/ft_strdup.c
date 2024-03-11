/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 00:44:40 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/11 01:02:10 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

static int ft_strlen(char *s)
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
    dup = malloc(sizeof(char) * (ft_strlen(s1) + 1));
    if (!dup)
		exit(1);
    while (*s1)
        dup[i++] = *s1++;
    dup[i] = '\0';
    return (dup);
}
