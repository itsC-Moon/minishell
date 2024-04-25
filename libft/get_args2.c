/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:15:30 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/21 12:26:41 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(const char *str)
{
	int		count;
	int		i;
	int		ret;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			return (count);
		ret = jump2(str + i, NULL);
		i += ret;
		count++;
	}
	return (count);
}

static char	*get_word2(const char *str)
{
	int		i;
	int		len;
	char	*s;

	jump2(str, &len);
	s = malloc(sizeof(char) * len + 1);
	check_null(s, "malloc");
	*s = 0;
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		len = word_s2(str + i, s + ft_strlen(s));
		len += quote_s2(str + len + i, SKIP, s + ft_strlen(s));
		i += len;
	}
	return (s);
}

static char	**alloc_buffer(const char *str)
{
	int		count;
	char	**strs;

	count = count_word(str);
	strs = malloc(sizeof(char **) * (count + 1));
	check_null(strs, "malloc");
	return (strs);
}

char	**split_arg(const char *str)
{
	int		i;
	int		count;
	char	**strs;

	strs = alloc_buffer(str);
	check_null(strs, "malloc");
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		strs[count] = get_word2(str + i);
		check_null(strs[count], "malloc");
		count++;
		i += jump2(str + i, NULL);
	}
	return (strs[count] = NULL, strs);
}
