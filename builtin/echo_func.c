/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 00:22:41 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/17 22:33:57 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_echo_args(char **args, int outfile)
{
	int i;

	i = 1;
	if (ft_strcmp(args[i], "-n") == 0)
		i++;
	while(args[i] != NULL)
	{
		ft_printf(outfile, "%s", args[i]);
		i++;
		if (args[i] != NULL)
			ft_printf(outfile, " ");
	}
}

int	echo_func(t_proc	*proc, int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	print_echo_args(proc->args, proc->io_fd[1]);
	if (ft_strcmp(proc->args[1], "-n") != 0)
		ft_printf(proc->io_fd[1], "\n");
	return (0);
}
