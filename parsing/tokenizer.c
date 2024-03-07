/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:06:04 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/07 15:43:34 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char *get_word(const char *str)
{
	// int i;
	// int len;
	char *s = NULL;

	// if (jump(str, &len) == -1)
	// 	return (NULL);
	// s = malloc(sizeof(char) * len + 1);
	// if (!s)
	// 	return (exit(1), NULL);
	// *s = 0;
	// i = 0;
	// while (str[i] && !is_sep(str[i]))
	// {
	// 	len = word_s(str + i, s + ft_strlen(s));
	// 	len += quote_s(str + len + i, SKIP, s + ft_strlen(s));
	// 	i += len;
	// }
	return (s);
}

int get_redir(const char *buffer, t_Token *tokens, t_Token_Type type)
{
	t_list *list;
	int offset;
	char *word;

	offset = 0;
	while (ft_isspace(buffer[offset]))
		offset++;
	if (ft_iskey(buffer[offset]))
		return (PARSING_ERROR);
	word = get_word(buffer + offset);
	list = lst(word, type);
	addback(tokens, list);
	return (offset);
}

int get_next_token(const char *buffer, t_Token *tokens)
{
	int offset;

	offset = 0;
	if (cmp(">>", buffer, 2) == 0)
		offset = get_redir(buffer + 2, tokens, APPEND_REDIRECT);
	else if (cmp(">", buffer, 2) == 0)
		offset = get_redir(buffer + 1, tokens, OUTPUT_REDIRECT);
	else if (cmp("<<", buffer, 2) == 0)
		offset = get_redir(buffer + 2, tokens, HEREDOC);
	else if (cmp("<", buffer, 2) == 0)
		offset = get_redir(buffer + 1, tokens, INPUT_redirect);
	else if (cmp("|", buffer, 2) == 0)
		offset = get_redir(buffer + 1, tokens, PIPE);
	return (offset);
}

void get_token(const char *buffer, t_Token *tokens)
{
	int offset;

	offset = 0;
	while (buffer[offset])
	{
		while (ft_isspace(buffer[offset]))
			offset++;
		if (buffer[offset] == '<' || buffer[offset] == '>' 
				|| buffer[offset] == '|')
			offset += get_next_token(buffer + offset, tokens);
		else
			offset += get_args(buffer + offset, tokens);
	}
}
t_Token *tokenizer(const char *buffer)
{
	t_Token *tokens;

	tokens = create_list();
	check_null(tokens, "malloc");
	get_token(buffer, tokens);
	return (tokens);
}
