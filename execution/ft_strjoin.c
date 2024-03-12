/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:51:10 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/12 02:19:57 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	strl2(char const	*s1, char const	*s2)
{
	int	i;

	i = 0;
	while (*s1 != 0)
	{
		i++;
		s1++;
	}
	while (*s2 != 0)
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
	if (rt == NULL)
		exit(1);
	while (*s1 != 0)
	{
		rt[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != 0)
	{
		rt[i] = *s2;
		s2++;
		i++;
	}
	rt[i] = 0;
	return (rt);
}
