/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:06:04 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/08 20:04:12 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <string.h>



int get_redir(const char *buffer, t_Token *tokens, t_Token_Type type)
{
	t_list	*list;
	int		offset;
	char	*word;

	offset = 0;
	word = NULL;
	while (ft_isspace(buffer[offset]))
		offset++;
	if (!buffer[offset] || ft_iskey(buffer[offset]))
		return (-5);
	if (type != PIPE)
		word = get_word(buffer + offset);
	if (!word && type != PIPE)
		return (-5);
	list = lst(word, type);
	addback(tokens, list);
	if (word)
		offset += jump(buffer + offset, NULL);
	return (offset);
}

int get_next_token(const char *buffer, t_Token *tokens)
{
	int offset;

	offset = 0;
	if (cmp(">>", buffer, 2) == 0)
		offset = get_redir(buffer + 2, tokens, APPEND_REDIRECT) + 2;
	else if (cmp(">", buffer, 1) == 0)
		offset = get_redir(buffer + 1, tokens, OUTPUT_REDIRECT) + 1;
	else if (cmp("<<", buffer, 2) == 0)
		offset = get_redir(buffer + 2, tokens, HEREDOC) + 2;
	else if (cmp("<", buffer, 1) == 0)
		offset = get_redir(buffer + 1, tokens, INPUT_REDIRECT) + 1;
	else if (cmp("|", buffer, 1) == 0)
		offset = get_redir(buffer + 1, tokens, PIPE) + 1;
	return (offset);
}

int get_token(const char *buffer, t_Token *tokens)
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
			i = get_args(buffer + offset, tokens);
		if (i <= 0)
			return (free_tokens(tokens), -5);
		offset += i;
	}
	return (0);
}
t_Token *tokenizer(const char *buffer)
{
	t_Token *tokens;

	tokens = create_list();
	check_null(tokens, "malloc");
	get_token(buffer, tokens);
	return (tokens);
}
