/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:03:18 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 18:56:38 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_command(t_Token *token)
{
	size_t	size;
	t_list	*it;

	size = 0;
	it = token->front;
	while (it)
	{
		if (it->type == PIPE)
			size++;
		it = it->next;
	}
	return (size + 1);
}

size_t	get_num_redic(t_list *list, t_Token_Type type)
{
	size_t	size;
	size_t	nb_str;

	size = 0;
	nb_str = 0;
	while (list && list->type != PIPE)
	{
		if (list->type == STRING_LTR)
			nb_str++;
		else
			size++;
		list = list->next;
	}
	if (type == STRING_LTR)
		return (nb_str);
	return (size);
}

t_file	file(char *file_name, t_open_type mod)
{
	t_file	file;

	file.file_name = file_name;
	file.mod = mod;
	file.limiter = NULL;
	if (file_name[0] == '$' && file_name[1])
		file.mod = AMBIGUOUS;
	return (file);
}

char	*remove_quote(const char *buffer)
{
	int		i;
	char	*str;
	int		len;

	len = 0;
	jump2(buffer, &len);
	str = malloc(len * sizeof(char) + 1);
	check_null(str, "malloc");
	i = 0;
	*str = 0;
	while (buffer[i])
	{
		if (is_quote(buffer[i]))
			i += quote_s(buffer + i, SKIP, str + ft_strlen(str));
		else
			i += word_s(buffer + i, str + ft_strlen(str));
	}
	return (str);
}

t_file	file_here(char *limiter, t_open_type mod)
{
	t_file	file;
	char	*str;
	char	*tmp;

	tmp = random_name((size_t)limiter);
	check_null(tmp, "malloc");
	str = ft_strjoin("/tmp/.doc", tmp);
	check_null(str, "malloc");
	file.state = _HEREDOC;
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '"'))
		file.state = NO_EXPAND;
	file.mod = mod;
	file.file_name = str;
	file.limiter = remove_quote(limiter);
	free(tmp);
	return (file);
}
