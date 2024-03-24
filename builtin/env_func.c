/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:02:19 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/23 13:43:09 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void print_env(t_env	*env, int	outfile)
{
	t_lst	*tmp;

	tmp = env->front;
	while (tmp != NULL)
	{
		ft_printf(outfile, "%s\n", tmp->varible);
		tmp = tmp->next;
	}
}

int env_func(t_proc	*proc, t_env	*env , int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	print_env(env, proc->io_fd[1]);
	return (0);
}
