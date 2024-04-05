/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/01 22:31:27 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "minishell.h"
#include <unistd.h>
// #include "minishell.h"

void  free_tab(char **tab)
{
	int i;

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

void  free_n_tab(char **tab, size_t size)
{
	size_t  i;

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

void free_file(t_file *file)
{
	free(file->limiter);	
	free(file->file_name);	
}

void free_proc(t_proc *proc)
{
	size_t i;

	i = 0;
	free_n_tab(proc->args, proc->nb_args);
	while (i < proc->nb_file)
		free_file(proc->file + i++);
	free(proc->file);
}

void clean_env(t_env *envp)
{
	t_lst *it;
	t_lst *tmp;

	it = envp->front;
	while (it)
	{
		tmp = it;
		it = it->next;
		free(tmp->varible);
		free(tmp);
	}
	free(envp->pwd);
	free(envp);
}
void	clean_mini(t_mini *mini)
{
	size_t i;

	i = 0;
	while (i < mini->nb_doc)
		unlink(mini->here_doc[i++].file_name);
	i = 0;
	while(i < mini->size) 
		free_proc(&mini->proc[i++]);
	free(mini->proc);
	free(mini->here_doc);
	mini->proc = NULL;
}
