/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:06:04 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/06 18:22:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void get_next_token(const char *buffer, t_Token *tokens)
{

}
// void get_redir(const char *buffer, t_Token *tokens)
// {
// 	t_list *list;
// 	
// 	list = get
// 	if (cmp(">>", buffer, 2) == 0)
// 			
// 	addback(tokens, list);
// 	
// }
void get_token(const char *buffer, t_Token *tokens)
{
	while(ft_isspace(*buffer))
		buffer++;
	if (cmp(">>", buffer, 2) == 0)
		get_next_token(buffer + 2, tokens);
		
}
t_Token *tokenizer(const char *buffer)
{
	t_Token *tokens;

	tokens = create_list();
	if (!tokens)
		exit(1);
	get_token(buffer, tokens);
	return (tokens);
}
