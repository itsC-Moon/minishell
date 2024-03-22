/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/21 23:45:58 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "minishell.h"
#include <sys/_types/_size_t.h>
// #include "minishell.h"

void  free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
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
	free(file);
}

void free_proc(t_proc *proc)
{
	size_t i;

	i = 0;
	free(proc->command);	
	free_tab(proc->args);
	while (i < proc->nb_file)
		free_file(proc->file + i++);
}

void free_env(t_env *envp)
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
	free(envp);
}
void	clean_mini(t_mini *mini)
{
	size_t i;

	i = 0;
	while(i < mini->size) 
		free_proc(&mini->proc[i++]);
	free(mini->proc);
}
