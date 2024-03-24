/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:32:55 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/24 01:32:56 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	print_echo_args(char **args, int outfile, int status)
{
	int i;

	(void)status;
	i = 1;
	if (ft_strcmp(args[i], "-n") == 0)
		i++;
	// if (ft_strcmp("$?", args[i]) == 0)
	// {
	// 	ft_printf(outfile, "%d", status);
	// 	return ;
	// }
	while(args[i] != NULL)
	{
		ft_printf(outfile, "%s", args[i]);
		i++;
		if (args[i] != NULL)
			ft_printf(outfile, " ");
	}
}

int	echo_func(t_proc	*proc, int *tmp, int status)
{
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	print_echo_args(proc->args, proc->io_fd[1], status);
	if (ft_strcmp(proc->args[1], "-n") != 0)
		ft_printf(proc->io_fd[1], "\n");
	return (close_builtin_file(tmp), close_fds(proc), 0);
}
