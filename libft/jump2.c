/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:17:05 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/01 22:31:10 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_s2(const char *str, char *buffer)
{
	int		i;

	i = 0;
	while (str[i] && !is_quote(str[i]) && !ft_isspace(str[i]))
	{
		if (buffer)
			buffer[i] = str[i];
		i++;
	}
	if (buffer)
		buffer[i] = '\0';
	return (i);
}

int	quote_s2(const char *str, int mod, char *buffer)
{
	int		i;
	char	quote;

	i = 0;
	quote = (*str == '\'') * '\'' + (*str == '"') * '"';
	if (quote == 0)
		return (0);
	str++;
	while (str[i] && str[i] != quote)
	{
		if (buffer)
			buffer[i] = str[i];
		i++;
	}
	if (!str[i])
		return (-1);
	if (buffer)
		buffer[i] = '\0';
	return (i + mod);
}

int	jump2(const char *str, int *len)
{
	int		i;
	int		ret;
	int		ret2;

	i = 0;
	if (len)
		*len = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		ret = quote_s2(str + i, SKIP, NULL);
		if (ret == -1)
			return (-1);
		ret2 = word_s2(str + ret + i, NULL);
		if (len)
		{
			*len += quote_s2(str + i, LEN, NULL);
			*len += word_s2(str + ret + i, NULL);
		}
		i += ret + ret2;
	}
	return (i);
}
