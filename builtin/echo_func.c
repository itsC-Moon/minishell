/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:32:55 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/18 21:04:50 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	print_echo_args(char **args, int outfile)
{
	int	i;
	int j;
	int check;

	i = 1;
	check = 0;
	while (1)
	{
		j = 0;
		if (args[i] == NULL || args[i][j++] != '-')
			break ;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != 0)
			break ;
		i++;
		check = 1;
	}
	while (args[i] != NULL)
	{
		ft_printf(outfile, "%s", args[i]);
		i++;
		if (args[i] != NULL)
			ft_printf(outfile, " ");
	}
	if (check == 0)
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
