/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:05:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 13:24:05 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	cmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	i = 0;
	while (i < n && (ptr1[i] || ptr2[i]))
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		i++;
	return (i);
}

int is_empty(const char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] && ft_isspace(buffer[i]))
		i++;
	if (!buffer[i])
		return (1);
	return (0); 
}
