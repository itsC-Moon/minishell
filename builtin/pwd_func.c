/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:08:32 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/26 03:37:32 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

char *set_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_printf(2, "nudejs-init: error retrieving current directory: getcwd:cannot access parent directories: %s \n", 
					strerror(errno)), NULL);
	return (pwd);
}

int	pwd_func(t_proc	*proc, t_env *env, int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	if (env->pwd == NULL)
		return (close_fds(proc), ft_printf(2, "nudejs-init: error retrieving current directory: getcwd:cannot access parent directories: No such file or directory \n"), 1);
	ft_printf(proc->io_fd[1], "%s\n", env->pwd);
	close_fds(proc);
	return (close_builtin_file(tmp), 0);
}
