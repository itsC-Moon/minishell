/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:29:56 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/25 03:06:08 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"
#include "../include/libft.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void close_fds(t_proc	*proc)
{
	unsigned int i;

	i = 0;
	while (i < proc->nb_file)
	{
		if (proc->file[i].fd != 0 && proc->file[i].fd != 1) 
			close (proc->file[i++].fd);
	}
}

static void	exec_cmd(t_proc	*proc, t_env	*env)
{
	open_files(proc);
	get_io_files(proc);
	proc->command = get_cmd_path(proc, env);
	check_cmd(proc, proc->command, NULL);
	dup2(proc->io_fd[0], 0);
	dup2(proc->io_fd[1], 1);
	close_fds(proc);
	execve(proc->command, proc->args, env_lst_to_arr(env));
	error_exit(proc->args[0], 126);
}

static int init_cmd(t_proc	*proc, t_env	*env, int mini_status)
{
	int pid;
	int status;
	
	if (proc->nb_args == 0 || proc->args[0] == NULL)
	{
		status = open_builtin_files(proc);
		if (status != 1)
			close_fds(proc);
		return (status);
	}
	status = init_builtin(proc, env, NULL, mini_status);
	if (status != -1)
		return (status);
	pid = fork();
	if (pid == 0)
		exec_cmd(proc, env);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	init_procs(t_mini	*mini)
{
	if (mini->nb_doc > 0)
		here_doc_exec(mini);
	if (mini->size == 1)
		mini->status = init_cmd(mini->proc, mini->envp, mini->status);
	else if (mini->size > 1)
		mini->status = init_pipe(mini->proc, mini->size, mini->envp, mini->status);
}

