/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:29:41 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/15 21:58:50 by hicham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/fcntl.h>
#include "minishell.h"
#include "libft.h"
#include "tmp.h"

void error_file(t_file file)
{
	ft_printf(2, "nudejs: %s: %s\n", file.file_name, strerror(errno));
	exit(1);
}

void open_files(t_proc	*proc)
{
	unsigned int i;

	i = 0;
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == INPUT)
			proc->file[i].fd = open(proc->file[i].file_name, O_RDONLY);
		else if (proc->file[i].mod == OUTPUT)
			proc->file[i].fd = open(proc->file[i].file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (proc->file[i].mod == APPEND)
			proc->file[i].fd = open(proc->file[i].file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (proc->file[i].fd < 0)
			error_file(proc->file[i]);
		i++;
	}
}

void get_io_files(t_proc	*proc)
{
	unsigned int i;

	i = 0;
	proc->io_fd[0] = 0;
	proc->io_fd[1] = 1;
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == OUTPUT
		|| proc->file[i].mod == APPEND)
			proc->io_fd[1] = proc->file[i].fd;
		else if (proc->file[i].mod == INPUT)
			proc->io_fd[0] = proc->file[i].fd;
		i++;
	}
}

void get_pipe_io_files(t_proc	*proc, int *fd)
{
	unsigned int i;

	i = 0;
	proc->io_fd[0] = -1;
	proc->io_fd[1] = -1;
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == OUTPUT
		|| proc->file[i].mod == APPEND)
			proc->io_fd[1] = proc->file[i].fd;
		else if (proc->file[i].mod == INPUT)
			proc->io_fd[0] = proc->file[i].fd;
		i++;
	}
	if (proc->io_fd[0] == -1)
		proc->io_fd[0] = fd[0];
	else
		close(fd[0]);
	if (proc->io_fd[1] == -1)
		proc->io_fd[1] = fd[1];
	else
		close(fd[1]);
}





















