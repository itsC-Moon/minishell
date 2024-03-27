/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:51:10 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/26 21:34:28 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	strl2(char const	*s1, char const	*s2)
{
	int	i;

	i = 0;
	while (s1 != NULL && *s1 != 0)
	{
		i++;
		s1++;
	}
	while (s2 != NULL && *s2 != 0)
	{
		i++;
		s2++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l;
	char	*rt;
	int		i;

	i = 0;
	l = strl2(s1, s2);
	rt = malloc(l + 1);
	check_null(rt, "malloc");
	while (s1 != NULL && *s1 != 0)
	{
		rt[i] = *s1;
		s1++;
		i++;
	}
	while (s2 != NULL && *s2 != 0)
	{
		rt[i] = *s2;
		s2++;
		i++;
	}
	rt[i] = 0;
	return (rt);
}
