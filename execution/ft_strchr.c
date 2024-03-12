/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:33:21 by zkotbi            #+#    #+#             */
/*   Updated: 2024/02/20 15:27:11 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

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
