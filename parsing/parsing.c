/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:20:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/09 17:46:24 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
char *get_file_name(const char *name)
{
	return ((char*)name);
}
char **_alloc(size_t n)
{
	char	**ptr;

	ptr = malloc((n + 1) * sizeof(char**));
	check_null(ptr, "mallco");
	ptr[n] = NULL;
	return (ptr);
}
char **get_args2(const char *buffer)
{
	(void)buffer;
	return (NULL);
}
void alloc_io(t_list *list, t_proc *proc)
{
	size_t	in;
	size_t	out;
	
	in = 0;
	out = 0;
	proc->input_file = _alloc(get_num_redic(list, INPUT));	
	proc->output_file = _alloc(get_num_redic(list, OUTPUT));	
	while (list && list->type != PIPE)
	{
		if (list->type == INPUT_REDIR || list->type == HEREDOC)
			proc->input_file[in++] = get_file_name(list->token);
		else if (list->type == INPUT_REDIR || list->type == APPEND_REDIR)
			proc->output_file[out++] = get_file_name(list->token);
		else if ( list->type == STRING_LTR)
			proc->args = get_args2(list->token);
		list = list->next;
	}
}

t_mini parsing(t_Token *tokens)
{
	t_mini	mini;
	size_t	i;
	t_proc	*it;
	t_list	*token;

	i = 0;
	mini.size = count_command(tokens);
	mini.proc = malloc(mini.size * sizeof(t_proc));
	check_null(mini.proc, "malloc");
	it = mini.proc;
	token = tokens->front;
	while (i < mini.size)
	{
		alloc_io(token, it + i);
		while (token && token->type != PIPE)
			token = token->next;
		i++;
	}
	return (mini);
}
t_mini parser(const char *buffer)
{
	t_mini	mini;
	t_Token *token;
	token = tokenizer(buffer);
	mini = parsing(token);
	return (mini);
}
