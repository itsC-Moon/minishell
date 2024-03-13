/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:51:18 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/13 15:16:01 by hibenouk         ###   ########.fr       */
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


int	jump_to_s(const char *str, char *new_buffer)
{
	int		i;
	int		j;

	if (new_buffer)
		j = ft_strlen(new_buffer);
	if (new_buffer)
		new_buffer[j++] = '\'';
	i = 1;
	while (str[i] != '\'')
	{
		if (new_buffer)
			new_buffer[j++] = str[i];
		i++;
	}
	if (new_buffer)
	{
		new_buffer[j++] = str[i];
		new_buffer[j] = '\0';
	}
	return (i + 1);
}

void copy_to_buffer(const char *buffer, char *new_buffer, t_env *envp)
{
	int		j;
	char	*new;
	
	new = env_search(envp, buffer);
	if (!new)
		return ;
	j = ft_strlen(new_buffer);
	while (*new)
		new_buffer[j++] = *(new++);
	new_buffer[j] = '\0';
}
