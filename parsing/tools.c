/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:51:18 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/09 15:58:48 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

size_t get_num_redic(t_list *list, t_Token_Type type)
{
	size_t in;
	size_t out;

	in = 0;
	out = 0;
	while (list && list->type != PIPE)
	{
		if (list->type  == INPUT_REDIR || list->type == HEREDOC)
			in++;
		if (list->type  == OUTPUT_REDIR || list->type == APPEND_REDIR)
			out++;
		list = list->next;
	}
	if (type == INPUT)
		return (in);
	return (out);
}
