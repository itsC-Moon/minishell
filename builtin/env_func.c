/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:33:19 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/21 12:27:46 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set_last_cmd(t_env	*env, char *cmd)
{
	t_lst	*lst;

	lst = env_search2(env, "_");
	if (lst == NULL)
		env_addback(env, make_lst(ft_strjoin("_=", cmd), DISPLAY));
	else
	{
		free(lst->varible);
		lst->varible = ft_strjoin("_=", cmd);
		lst->state = DISPLAY;
	}
}

static void	print_env(t_env	*env, int outfile)
{
	t_lst	*tmp;

	tmp = env->front;
	while (tmp != NULL)
	{
		if (tmp->state == DISPLAY)
			ft_printf(outfile, "%s\n", tmp->varible);
		tmp = tmp->next;
	}
}

int	env_func(t_proc	*proc, t_env	*env, int *tmp)
{
	int	code;

	code = 0;
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	if (proc->args[1] == NULL)
		print_env(env, proc->io_fd[1]);
	else
	{
		ft_printf(2, "nudejs: env: No option No arguments\n");
		code = 1;
	}
	return (close_builtin_file(tmp), close_fds(proc), code);
}
