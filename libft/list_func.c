/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:14:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/06 15:07:11 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_Token *create_list()
{
	t_Token *token;
	token = malloc(sizeof(t_Token));
	if (!token)
		return (error("malloc"), NULL);
	token->size = 0;
	token->back = NULL;
	token->front = NULL;
	return (token);
}

t_list *lst(char *token, t_Token_Type token_type)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->token = token;
	list->type = token_type;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

void addfront(t_Token *token, t_list *list)
{
	if (token->size == 0)		
	{
		token->front = list;
		token->back = list;
		token->size = 1;
		return ;
	}
	list->next = token->front;
	token->front->prev = list;
	token->front = list;
	token->size += 1;	
}


void addback(t_Token *token, t_list *list)
{
	if (token->size == 0)		
	{
		token->back = list;
		token->front = list;
		token->size = 1;
		return ;
	}
	list->prev = token->back;
	token->back->next = list;
	token->back = list;
	token->size += 1;	
}

