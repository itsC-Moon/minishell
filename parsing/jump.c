/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:17:05 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/19 14:24:06 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *get_word(const char *str)
{
	int		i;
	int		len;
	char	*s;

	if (!str || !*str)
		return (NULL);
	if (jump(str, &len) < 0)
		return (NULL);
	s = malloc(sizeof(char) * len + 1);
	check_null(s, "malloc");
	*s = 0;
	i = 0;
	while (str[i] && !is_sep(str[i]))
	{
		len = word_s(str + i, s + ft_strlen(s));
		len += quote_s(str + len + i, SKIP, s + ft_strlen(s));
		i += len;
	}
	return (s);
}

