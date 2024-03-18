/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:59:43 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/18 20:41:02 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
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
	dup2(proc->io_fd[0], 0);
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
	pipe(fd);
	tmp[1] = fd[1];
	if (i == 0)
		tmp[0] = 0;
	else if (i == size -1)
		tmp[1] = 1;
}

int	init_pipe(t_proc *proc, unsigned int size, t_env *envp)
{
	unsigned int i;
	int status;
	// int status_builtin; 
	int *pids;
	int fd[2] =  {0, 0};
	int tmp[2];

	i = 0;
	pids = malloc(sizeof(int) * size);
	check_null(pids, "malloc");
	while (i < size)
	{
		pipe_file(tmp, fd, i, size);
		// status_builtin = init_builtin(proc, envp, tmp);
		pids[i] = fork();
		if (pids[i] == 0)
			child(&proc[i], envp, tmp);
		close(tmp[0]);
		close(tmp[1]);
		i++;
	}
	wait_process(pids, &status, size);
	// if (status_builtin != -1)
		// return(free(pids), status_builtin);
	return (free(pids), WEXITSTATUS(status));
}
