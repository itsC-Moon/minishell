/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:08:32 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/21 12:29:25 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_pwd(void)
{
	char	*pwd;
	char	*str1;
	char	*str2;

	str1 = "nudejs-init: error retrieving current directory: ";
	str2 = "getcwd: cannot access parent directories:";
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_printf(2, "%s%s %s \n",
				str1, str2, strerror(errno)), NULL);
	return (pwd);
}

int	pwd_func(t_proc	*proc, t_env *env, int *tmp)
{
	char	*str1;
	char	*str2;

	str1 = "nudejs-init: error retrieving current directory: ";
	str2 = "getcwd: cannot access parent directories";
	if (open_builtin_files(proc) == 1)
		return (1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	if (env->pwd == NULL)
		return (close_fds(proc),
			ft_printf(2, "%s%s\n", str1, str2), 1);
	ft_printf(proc->io_fd[1], "%s\n", env->pwd);
	close_fds(proc);
	return (close_builtin_file(tmp), 0);
}
