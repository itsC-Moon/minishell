/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 20:54:50 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_n_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

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
