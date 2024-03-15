/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:06:04 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/14 16:11:42 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int get_pipe(const char *buffer, t_Token *tokens, t_Token_Type type)
{
	t_list	*list;
	int		offset;

	offset = 0;
	if (type == PIPE && !tokens->front)
		return (-42);
	while (ft_isspace(buffer[offset]))
		offset++;
	if (!buffer[offset] || buffer[offset] == '|')
		return (-42);
	list = lst(NULL, type);
	check_null(list, "malloc");
	addback(tokens, list);
	return (offset);
}

static int get_redir(const char *buffer, t_Token *tokens, t_Token_Type type)
{
	int		offset;
	int		check;

	offset = 0;
	while (ft_isspace(buffer[offset]))
		offset++;
	if (!buffer[offset] || ft_iskey(buffer[offset]))
		return (-42);
	check = get_args(buffer + offset, tokens, is_sep);
	tokens->back->type = type;
	if (check < 0)
		return (-42);
	return (offset + check);
}

static int get_next_token(const char *buffer, t_Token *tokens)
{
	int offset;

	offset = 0;
	if (cmp(">>", buffer, 2) == 0)
		offset = get_redir(buffer + 2, tokens, APPEND_REDIR) + 2;
	else if (cmp(">", buffer, 1) == 0)
		offset = get_redir(buffer + 1, tokens, OUTPUT_REDIR) + 1;
	else if (cmp("<<", buffer, 2) == 0)
		offset = get_redir(buffer + 2, tokens, HEREDOC) + 2;
	else if (cmp("<", buffer, 1) == 0)
		offset = get_redir(buffer + 1, tokens, INPUT_REDIR) + 1;
	else if (cmp("|", buffer, 1) == 0)
		offset = get_pipe(buffer + 1, tokens, PIPE) + 1;
	return (offset);
}

static int get_token(const char *buffer, t_Token *tokens)
{
	int		offset;
	int		i;

	i = 0;
	offset = 0;
	while (buffer[offset])
	{
		while (ft_isspace(buffer[offset]))
			offset++;
		if (buffer[offset] == '<' || buffer[offset] == '>' 
				|| buffer[offset] == '|')
			i = get_next_token(buffer + offset, tokens);
		else
			i = get_args(buffer + offset, tokens, is_sep);
		if (i <= 0)
			return (free_tokens(tokens), -42);
		offset += i;
	}
	return (0);
}
t_Token *tokenizer(const char *buffer)
{
	t_Token *tokens;

	tokens = create_list();
	check_null(tokens, "malloc");
	if(get_token(buffer, tokens)<0)
		exit(3);//TODO : check for error -42 and free tokens
	return (tokens);
}
