/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:33:21 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/12 13:06:44 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char	*s, int c)
{
	char	i;

	i = (char )c;
	if (s == NULL)
		return (NULL);
	while (*s != 0)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (i != 0)
	{
		return (NULL);
	}
	return ((char *)s);
}
