/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:20:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/21 15:59:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void __alloc(t_list *list, t_proc *proc)
{
	proc->nb_file = get_num_redic(list, INPUT_REDIR);
	proc->nb_args = get_num_redic(list, STRING_LTR);
	proc->args = malloc(sizeof(char **) * (proc->nb_args + 1));
	check_null(proc->args, "malloc");
	proc->file = malloc(sizeof(t_file) * proc->nb_file);
	check_null(proc->file, "malloc");
}

static void alloc_io(t_list *list, t_proc *proc, t_env *envp)
{
	size_t it;
	size_t i;

	it = 0;
	i = 0;
	if (list && list->type == PIPE)
		list = list->next;
	__alloc(list, proc);
	while (list && list->type != PIPE)
	{
		if (list->type == STRING_LTR)
			proc->args[i++] = expand(list->token, envp);
		else if (list->type == INPUT_REDIR)
			proc->file[it++] = file(expand(list->token, envp), INPUT);
		else if (list->type == OUTPUT_REDIR)
			proc->file[it++] = file(expand(list->token, envp), OUTPUT);
		else if (list->type == APPEND_REDIR)
			proc->file[it++] = file(expand(list->token, envp), APPEND);
		else if (list->type == HEREDOC)
			proc->file[it++] = file_here(list->token, _HEREDOC);
		if (list->type == STRING_LTR && !proc->args[i - 1])
			i--;
		list = list->next;
	}
	proc->nb_args = i;
	UINT(i);
	proc->args[i] = NULL;
}

static t_mini parsing(t_Token *tokens, t_env *envp)
{
	t_mini	mini;
	size_t 	i;
	t_proc 	*it;
	t_list 	*token;

	i = 0;
	mini.size = count_command(tokens);
	mini.proc = malloc(mini.size * sizeof(t_proc));
	check_null(mini.proc, "malloc");
	it = mini.proc;
	token = tokens->front;
	while (i < mini.size)
	{
		alloc_io(token, it + i, envp);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
		i++;
	}
	return (mini);
}

t_mini parser(const char *buffer, t_env *envp)
{
	t_mini	mini;
	t_Token *tokens;

	tokens = tokenizer(buffer);
	if (!tokens)
		return ((t_mini){0});
	mini = parsing(tokens, envp);
	free_tokens(tokens);
	free(tokens);
	mini.envp = envp;
	init_here_doc(&mini);
	return (mini);
}
