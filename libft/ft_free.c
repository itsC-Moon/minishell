/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/08 18:43:05 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_list(t_list *list)
{
	free(list->token);
	free(list);
}

void	free_tokens(t_Token *token)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = token->front;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free_list(tmp);
	}
	token->front = NULL;
	token->back = NULL;
	token->size = 0;
}
