/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:57:48 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/18 18:46:59 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	cd_files_handle(t_proc *proc, int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	return (0);
}

static int	error_func(t_proc *proc, char *str, int *tmp)
{
	close_builtin_file(tmp);
	close_fds(proc);
	ft_printf(2, "nudejs: %s: %s :%s\n", proc->args[0], proc->args[1], str);
	return (1);
}

static int	go_home(t_env *env, t_proc *proc, int *tmp)
{
	char	*home;

	if (env->pwd == NULL)
		return (0);
	home = env_search(env, "HOME");
	if (home == NULL)
		return (error_func(proc, "HOME not set", tmp));
	if (chdir(home) < 0)
		return (error_func(proc, strerror(errno), tmp));
	set_env_vars(env, proc);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

static int	go_to_prev(t_env *env, t_proc *proc, int *tmp)
{
	char	*pwdold_var;

	if (env->pwd == NULL)
		return (0);
	pwdold_var = env_search(env, "OLDPWD");
	if (pwdold_var == NULL)
		return (error_func(proc, "OLDPWD not set", tmp));
	if (pwdold_var[0] == 0)
		return (0);
	if (chdir(pwdold_var) == -1)
		return (error_func(proc, strerror(errno), tmp));
	ft_printf(proc->io_fd[1], "%s\n", pwdold_var);
	set_env_vars(env, proc);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

int	cd_func(t_proc *proc, t_env *env, int *tmp)
{
	if (cd_files_handle(proc, tmp) == 1)
		return (1);
	if (proc->args[1] == NULL)
		return (go_home(env, proc, tmp));
	else if (proc->args[1][0] == '-')
		return (go_to_prev(env, proc, tmp));
	else if (proc->args[1][0] != 0 && chdir(proc->args[1]) < 0)
		return (error_func(proc, strerror(errno), tmp));
	set_env_vars(env, proc);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}
