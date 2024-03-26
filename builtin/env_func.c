/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:33:19 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/26 14:44:29 by hibenouk         ###   ########.fr       */
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
		if (tmp->state == DISP)
			ft_printf(outfile, "%s\n", tmp->varible);
		tmp = tmp->next;
	}
}

int env_func(t_proc	*proc, t_env	*env , int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	print_env(env, proc->io_fd[1]);
	return (close_builtin_file(tmp), close_fds(proc), 0);
}
