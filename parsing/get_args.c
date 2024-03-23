/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:18:31 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/21 22:18:00 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int get_len(const char *buffer, int (*func)(char))
{
	int		i;
	int		l;

	i = 0;
	while (buffer[i] && !func(buffer[i]))
	{
		if (is_quote(buffer[i]))
		{
			l = quote_s(buffer+ i, SKIP, NULL);
			if (l < 0)
				return (-42);
			i += l;
		}
		else
			i++;
	}
	return (i);
}


int	get_args(const char *buffer, t_Token *tokens, int (*func)(char))
{
	int		i;
	int		len;
	char	*args;
	t_list	*list;
	
	len = get_len(buffer, func);
	if (len < 0)
		return (-42);
	args = malloc(sizeof(char) * len + 1);
	check_null(args, "malloc");
	i = -1;
	while (++i < len)
		args[i] = buffer[i];
	args[i] = '\0';
	list = lst(args, STRING_LTR);
	check_null(list, "malloc");
	addback(tokens, list);
	return (len);
}

int	word_s(const char *str, char *buffer)
{
	int		i;

	i = 0;
	while (str[i] && !is_quote(str[i]) && !is_sep(str[i]))
	{
		if (buffer)
			buffer[i] = str[i];
		i++;
	}
	if (buffer)
		buffer[i] = '\0';
	return (i);
}

int	quote_s(const char *str, int mod, char *buffer)
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
		return (report("syntax error unclosed quote"), -42);
	if (buffer)
		buffer[i] = '\0';
	return (i + mod);
}

int	jump(const char *str, int *len)
{
	int		i;
	int		ret;
	int		ret2;

	i = 0;
	if (len)
		*len = 0;
	while (str[i] && !is_sep(str[i]))
	{
		ret = quote_s(str + i, SKIP, NULL);
		if (ret <= -1)
			return (-5);
		ret2 = word_s(str + ret + i, NULL);
		if (len)
		{
			*len += quote_s(str + i, LEN, NULL);
			*len += word_s(str + ret + i, NULL);
		}
		i += ret + ret2;
	}
	return (i);
}
