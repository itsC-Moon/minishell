/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:25:46 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/12 13:09:09 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	**ft_free(char	**rt, int k)
// {
// 	while (k >= 0)
// 	{
// 		free (rt[k]);
// 		k--;
// 	}
// 	free(rt);
// 	return (NULL);
// }

static char	*ftstrcpy(const char	*str, int i, int j, char	*s2)
{
	int	k;

	k = 0;
	while (i < j)
	{
		s2[k] = str[i];
		k++;
		i++;
	}
	s2[k] = 0;
	return (s2);
}

static int	count(const char	*s, char c)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] && s[i] != c)
			i++;
		k++;
	}
	return (k);
}

char	**ft_split(char *s, char c)
{
	char	**rt;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	rt = malloc(sizeof(char *) * (count(s, c) + 1));
	check_null(rt, "malloc");
	while (i[1] < count(s, c))
	{
		while (s[*i] && s[*i] == c)
			i[0]++;
		i[2] = 0;
		while (s[*i] && s[*i] != c)
		{
			i[2]++;
			i[0]++;
		}
		rt[i[1]] = malloc(i[2] + 1);
		check_null(rt[i[1]], "malloc");
		ftstrcpy(s, i[0] - i[2], i[0], rt[i[1]++]);
	}
	rt[i[1]] = NULL;
	return (rt);
}
