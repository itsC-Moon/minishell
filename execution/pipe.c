/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:59:43 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/19 21:22:00 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <sys/wait.h>
#include <unistd.h>
#include "tmp.h"

void	child(t_proc	*proc, t_env	*env, int *fd)
{
	int status;

	status = init_builtin(proc, env, fd);
	if (status != -1)
		exit(status);
	open_files(proc);
	get_pipe_io_files(proc, fd);
	proc->command = get_cmd_path(proc, env);
	check_cmd(proc, proc->command);
	if (proc->io_fd[0] != 0)
		dup2(proc->io_fd[0], 0);
	if (proc->io_fd[1] != 1)
		dup2(proc->io_fd[1], 1);
	execve(proc->command, proc->args, env_lst_to_arr(env));
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

void pipe_file(int *tmp, int *fd, int i, int size)
{
	tmp[0] = fd[0];
	if (i != size -1)
	{
		pipe(fd);
		tmp[1] = fd[1];
	}
	if (i == 0 )
		tmp[0] = 0;
	else if (i == size -1)
		tmp[1] = 1;
}

void ft_close(int *fd)
{
	if (*fd <= 1)
		return ;
	close(*fd);
	*fd = -1;
}
int	init_pipe(t_proc *proc, unsigned int size, t_env *envp)
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
		pipe_file(tmp, fd, i, size);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i < size - 1)
				ft_close(&fd[0]);
			child(&proc[i], envp, tmp);
		}
		ft_close(&tmp[0]);
		ft_close(&tmp[1]);
		i++;
	}
	wait_process(pids, &status, size);
	return (free(pids), WEXITSTATUS(status));
}
