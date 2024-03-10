/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:51:18 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/10 14:56:04 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

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

size_t get_num_redic(t_list *list)
{
	size_t size;

	size = 0;
	while (list && list->type != PIPE)
	{
		if (list->type != STRING_LTR)
			size++;
		list = list->next;
	}
	return (size);
}

t_file *file(char *file_name, t_open_type mod)
{
	t_file *file;

	file = malloc(sizeof(t_file));
	check_null(file, "malloc");
	file->file_name = file_name;
	file->mod = mod;
	return (file);
}


