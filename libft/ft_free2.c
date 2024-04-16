/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:49:06 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 20:55:45 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(t_env *envp)
{
	t_lst	*it;
	t_lst	*tmp;

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

static void	free_file(t_file *file)
{
	free(file->limiter);
	free(file->file_name);
}

static void	free_proc(t_proc *proc)
{
	size_t	i;

	i = 0;
	free_n_tab(proc->args, proc->nb_args);
	while (i < proc->nb_file)
		free_file(proc->file + i++);
	free(proc->file);
}

void	clean_mini(t_mini *mini)
{
	size_t	i;

	i = 0;
	while (i < mini->nb_doc)
		unlink(mini->here_doc[i++].file_name);
	i = 0;
	while (i < mini->size)
		free_proc(&mini->proc[i++]);
	free(mini->proc);
	free(mini->here_doc);
	mini->proc = NULL;
}
