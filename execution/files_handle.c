/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:29:41 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/21 12:29:50 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_file(t_proc *proc, int size)
{
	int	i;

	i = 0;
	while (i < size)
		close(proc->file[i++].fd);
	ft_printf(2, "nudejs: %s: %s\n", proc->file[i].file_name, strerror(errno));
	exit(1);
}

void	open_files(t_proc	*proc)
{
	size_t	i;

	i = 0;
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == INPUT)
			proc->file[i].fd = open(proc->file[i].file_name, O_RDONLY);
		if (proc->file[i].mod == _HEREDOC)
			proc->file[i].fd = open(proc->file[i].file_name, O_RDONLY);
		else if (proc->file[i].mod == OUTPUT)
			proc->file[i].fd = open(proc->file[i].file_name, O_CREAT
					| O_WRONLY | O_TRUNC, 0644);
		else if (proc->file[i].mod == APPEND)
			proc->file[i].fd = open(proc->file[i].file_name, O_CREAT
					| O_WRONLY | O_APPEND, 0644);
		if (proc->file[i].fd < 0)
			error_file(proc, i);
		if (proc->file[i].mod == AMBIGUOUS)
		{
			ft_printf(2, "nudejs: %s: %s\n",
				proc->file[i].file_name, "ambiguous redirect");
			exit(1);
		}
		i++;
	}
}

void	get_io_files(t_proc	*proc)
{
	size_t	i;

	i = 0;
	proc->io_fd[0] = 0;
	proc->io_fd[1] = 1;
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == OUTPUT
			|| proc->file[i].mod == APPEND)
			proc->io_fd[1] = proc->file[i].fd;
		else if (proc->file[i].mod == INPUT
			|| proc->file[i].mod == _HEREDOC)
			proc->io_fd[0] = proc->file[i].fd;
		i++;
	}
}

void	get_pipe_io_files(t_proc	*proc, int *fd)
{
	size_t	i;

	i = 0;
	proc->io_fd[0] = fd[0];
	proc->io_fd[1] = fd[1];
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == OUTPUT
			|| proc->file[i].mod == APPEND)
			proc->io_fd[1] = proc->file[i].fd;
		else if (proc->file[i].mod == INPUT
			|| proc->file[i].mod == _HEREDOC)
			proc->io_fd[0] = proc->file[i].fd;
		i++;
	}
}
