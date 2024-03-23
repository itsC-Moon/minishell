/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:59:43 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/23 03:55:20 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <sys/wait.h>
#include <unistd.h>
#include "tmp.h"

void ft_close(int *fd)
{
	if (*fd <= 1)
		return ;
	close(*fd);
	*fd = -1;
}

void	child(t_proc	*proc, t_env	*env, int *fd, int mini_status)
{
	int status;

	if (proc->args == NULL || proc->args[0] == NULL)
		exit(open_builtin_files(proc));
	status = init_builtin(proc, env, fd, mini_status);
	if (status != -1)
		exit(status);
	open_files(proc);
	get_pipe_io_files(proc, fd);
	proc->command = get_cmd_path(proc, env);
	check_cmd(proc, proc->command, fd);
	if (proc->io_fd[0] != 0)
	{
		dup2(proc->io_fd[0], 0);
		ft_close (&proc->io_fd[0]);
	}
	if (proc->io_fd[1] != 1)
	{
		dup2(proc->io_fd[1], 1);
		ft_close(&proc->io_fd[1]);
	}
	close_fds(proc);
	execve(proc->command, proc->args, env_lst_to_arr(env));
	error_exit(proc->args[0], 126);
}

void wait_process(int *pids, int *status, int size)
{
	int i = 0;
	while (i < size)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
}


int pipe_file(int *tmp, int *fd, int i, int size)
{
	tmp[0] = fd[0];
	if (i != size -1)
	{
		if (pipe(fd) < 0)
			return (ft_close(&tmp[0]), 1);
		tmp[1] = fd[1];
	}
	if (i == 0 )
		tmp[0] = 0;
	else if (i == size -1)
		tmp[1] = 1;
	return (0);
}

int	init_pipe(t_proc *proc, unsigned int size, t_env *envp, int mini_status)
{
	size_t i;
	int status;
	int *pids;
	int fd[2] =  {0, 0};
	int tmp[2] = {-1};

	i = 0;
	pids = malloc(sizeof(int) * size);
	check_null(pids, "malloc");
	while (i < size)
	{
		if (pipe_file(tmp, fd, i, size) == 1)
			return (free(pids), 1);	
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i < size - 1)
				ft_close(&fd[0]);
			child(&proc[i], envp, tmp, mini_status);
		}
		ft_close(&tmp[0]);
		ft_close(&tmp[1]);
		i++;
	}
	wait_process(pids, &status, size);
	return (free(pids), WEXITSTATUS(status));
}
