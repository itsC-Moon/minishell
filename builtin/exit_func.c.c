/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 01:08:38 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/23 01:49:48 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int exit_func(t_proc	*proc, int *tmp)
{
	close_builtin_file(tmp);
	if (open_builtin_files(proc) == 1)
		return (1);
	close_fds(proc);
	if (proc->nb_args > 2)
	{
		ft_printf(2, "nudejs: exit: too many arguments\n");
		return (1);
	}
	if (proc->nb_args == 2)
		exit(ft_atoi(proc->args[1]));
	else
		exit(0);
	return (0);
}
