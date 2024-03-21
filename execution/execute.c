/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:31:36 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/21 13:35:41 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"
#include "tmp.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_cmd(t_proc	*proc, t_env	*env)
{
	open_files(proc);
	get_io_files(proc);
	proc->command = get_cmd_path(proc, env);
	check_cmd(proc, proc->command);
	dup2(proc->io_fd[0], 0);
	dup2(proc->io_fd[1], 1);
	execve(proc->command, proc->args, env_lst_to_arr(env));
	error_exit(proc->args[0], 126);
}

int init_cmd(t_proc	*proc, t_env	*env, int mini_status)
{
	int pid;
	int status;
	
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
	if (mini->proc->args[0] == NULL)
	{
		if (mini->nb_doc > 0)
			mini->status = open_builtin_files(mini->proc);
		else
			mini->status = 0;
		return ;
	}
	if (mini->size == 1)
		mini->status = init_cmd(mini->proc, mini->envp, mini->status);
	else if (mini->size > 1)
		mini->status = init_pipe(mini->proc, mini->size, mini->envp, mini->status);
}

