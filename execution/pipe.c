/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:59:43 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/05 00:40:09 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <sys/wait.h>

static void	ft_close(int *fd)
{
	if (*fd <= 1)
		return ;
	close(*fd);
	*fd = -1;
}

static void	child(t_proc	*proc, t_env	*env, int *fd, int mini_status)
{
	int	status;

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
	env_set_last_cmd(env, proc->command);
	execve(proc->command, proc->args, env_lst_to_arr(env));
	error_exit(proc->args[0], 126);
}

static void	wait_process(int *pids, int *status, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
}

static int	pipe_file(int *tmp, int *fd, int i, int size)
{
	tmp[0] = fd[0];
	if (i != size -1)
	{
		if (pipe(fd) < 0)
			return (ft_close(&tmp[0]), 1);
		tmp[1] = fd[1];
	}
	if (i == 0)
		tmp[0] = 0;
	else if (i == size -1)
		tmp[1] = 1;
	return (0);
}

int	init_pipe(t_proc *proc, unsigned int size, t_env *envp, int mini_status)
{
	t_pipe	*pipe;
	int		status;

	pipe = init_pipe_struct(size);
	while (pipe->i < size)
	{
		if (pipe_file(pipe->tmp, pipe->fd, pipe->i, size) == 1)
			return (free(pipe->pids), free(pipe), 1);
		pipe->pids[pipe->i] = fork();
		if (pipe->pids[pipe->i] == 0)
		{
			if (pipe->i < size - 1)
				ft_close(&(pipe->fd[0]));
			child(&proc[pipe->i], envp, pipe->tmp, mini_status);
		}
		ft_close(&(pipe->tmp[0]));
		ft_close(&(pipe->tmp[1]));
		pipe->i++;
	}
	wait_process(pipe->pids, &status, size);
	remove_node(envp, env_search_2(envp, "_"));
	return (free(pipe->pids), free(pipe), WEXITSTATUS(status));
}
