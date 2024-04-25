/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:32:55 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/21 12:30:50 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo_args(char **args, int outfile)
{
	int	it[3];

	it[0] = 1;
	it[1] = 0;
	while (1)
	{
		it[2] = 0;
		if (args[it[0]] == NULL || args[it[0]][it[2]++] != '-')
			break ;
		while (args[it[0]][it[2]] == 'n')
			it[2]++;
		if (args[it[0]][it[2]] != 0 || it[2] == 1)
			break ;
		it[0]++;
		it[1] = 1;
	}
	while (args[it[0]] != NULL)
	{
		ft_printf(outfile, "%s", args[it[0]]);
		it[0]++;
		if (args[it[0]] != NULL)
			ft_printf(outfile, " ");
	}
	if (it[1] == 0)
		ft_printf(outfile, "\n");
}

int	echo_func(t_proc	*proc, int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	print_echo_args(proc->args, proc->io_fd[1]);
	return (close_builtin_file(tmp), close_fds(proc), 0);
}
