/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:29 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 18:38:04 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_doc(t_mini *mini)
{
	size_t	size;
	size_t	i;
	size_t	j;
	t_proc	*proc;

	size = 0;
	i = 0;
	while (i < mini->size)
	{
		j = 0;
		proc = mini->proc + i;
		while (j < proc->nb_file)
		{
			if (proc->file[j].mod == _HEREDOC)
				size++;
			j++;
		}
		i++;
	}
	return (size);
}

void	init_here_doc(t_mini *mini)
{
	size_t	i;
	size_t	j;
	size_t	size;
	t_proc	*proc;

	mini->nb_doc = count_doc(mini);
	mini->here_doc = NULL;
	if (mini->nb_doc == 0)
		return ;
	mini->here_doc = malloc(sizeof(t_file) * mini->nb_doc);
	check_null(mini->here_doc, "malloc");
	i = 0;
	size = 0;
	while (i < mini->size)
	{
		j = 0;
		proc = mini->proc + i;
		while (j < proc->nb_file)
		{
			if (proc->file[j].mod == _HEREDOC)
				mini->here_doc[size++] = proc->file[j];
			j++;
		}
		i++;
	}
}
