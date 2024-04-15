/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:57:48 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/15 17:19:58 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int cd_files_handle(t_proc *proc, int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	return (0);
}

char *get_pwd(t_env *env, t_proc *proc)
{
	char *pwd;
	char *tmp;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		return (pwd);
	if (env->pwd == NULL)
		return (ft_strdup(proc->args[1]));
	pwd = ft_strjoin(env->pwd, "/");
	tmp = ft_strjoin(pwd, proc->args[1]);
	return (free(pwd), tmp);
}

void set_env_var(t_env *env, t_proc *proc)
{
	t_lst *lst_pwd;
	t_lst *lst_old;
	char *tmp;

	tmp = get_pwd(env, proc);
	free(env->pwd);
	env->pwd = tmp;
	lst_pwd = env_search2(env, "PWD");
	lst_old = env_search2(env, "OLDPWD");
	if (lst_pwd == NULL)
	{
		remove_node(env, lst_old);
		return ;
	}
	free(lst_old->varible);
	lst_old->varible = ft_strjoin("OLD", lst_pwd->varible);
	free(lst_pwd->varible);
	lst_pwd->varible = ft_strjoin("PWD=", env->pwd);
}
static int error_func(t_proc *proc, char *str, int *tmp)
{
	close_builtin_file(tmp);
	close_fds(proc);
	ft_printf(2, "nudejs: %s: %s :%s\n", proc->args[0], proc->args[1], str);	
	return (1);
}

// static void	set_env_variale(t_env *env, char *old_pwd)
// {
// 	t_lst *lst;
// 	char *pwd;

// 	pwd = getcwd(NULL, 0);
// 	if (pwd == NULL)
// 		return ;
// 	if (old_pwd == NULL)
// 		old_pwd = env->pwd;
// 	else
// 		free(env->pwd);
// 	env->pwd = pwd;
// 	lst = env_search_2(env, "OLDPWD");
// 	if (lst != NULL && old_pwd != NULL)
// 	{
// 		free(lst->varible);
// 		lst->varible = ft_strjoin("OLDPWD=", old_pwd);
// 		free(old_pwd);
// 	}
// 	lst = env_search_2(env, "PWD");
// 	if (lst != NULL && pwd != NULL)
// 	{
// 		free(lst->varible);
// 		lst->varible = ft_strjoin("PWD=", pwd);
// 	}
// }


// static void	set_env_variale_2(t_env *env, char *old_pwd, char *pwd)
// {
// 	t_lst *lst;

// 	lst = env_search_2(env, "OLDPWD");
// 	if (lst != NULL && old_pwd != NULL)
// 	{
// 		free(lst->varible);
// 		lst->varible = ft_strjoin("OLDPWD=", old_pwd);
// 		free(old_pwd);
// 	}
// 	lst = env_search_2(env, "PWD");
// 	if (lst != NULL && pwd != NULL)
// 	{
// 		free(lst->varible);
// 		lst->varible = ft_strjoin("PWD=", pwd);
// 	}
// }


static int go_home(t_env *env, t_proc *proc, int *tmp)
{
	char *home;

	if (env->pwd == NULL)
		return (0);
	home = env_search(env, "HOME");
	if (home == NULL)
		return (error_func(proc, "HOME not set", tmp));
	if (chdir(home) < 0)
		return (error_func(proc, strerror(errno), tmp));
	set_env_var(env, proc);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

static int go_to_prev(t_env *env, t_proc *proc, int *tmp)
{
	char *pwdold_var;

	if (env->pwd == NULL)
		return (0);
	pwdold_var = env_search(env, "OLDPWD");
	if (pwdold_var == NULL)
		return (error_func(proc, "OLDPWD not set", tmp));
	if (pwdold_var[0] == 0)
		return (0); 
	if (chdir(pwdold_var) < 0)
		return ( error_func(proc, strerror(errno), tmp));
	ft_printf(proc->io_fd[1], "%s\n", pwdold_var);
	set_env_var(env, proc);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

int cd_func(t_proc *proc, t_env *env, int *tmp)
{
	if (cd_files_handle(proc, tmp) == 1)
		return (1);
	if (proc->args[1] == NULL)
		return (go_home(env, proc, tmp));
	else if (proc->args[1][0] == '-')
		return (go_to_prev(env, proc, tmp));
	else if (proc->args[1][0] != 0 && chdir(proc->args[1]) < 0)
		return (error_func(proc, strerror(errno), tmp));
	set_env_var(env, proc);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

// void cd_set_pwd(char *dir_to, t_env	*env, t_proc *proc, int *fd)
// {
// 	char *tmp;
// 	char *tmp1;

// 	if (env->pwd != NULL)
// 	{
// 		tmp1 = ft_strjoin("/", dir_to);
// 		tmp = ft_strjoin(env->pwd, tmp1);
// 		free(tmp1);
// 		tmp1 = env->pwd;
// 		env->pwd = tmp;
// 	}
// 	else
// 	{
// 		ft_printf(2, "cd: error retrieving current directory\n");
// 		tmp = ft_strjoin(env->pwd, dir_to);
// 		tmp1 = env->pwd;
// 		env->pwd = tmp;
// 	}
// 	set_env_variale_2(env, tmp1, tmp);
// 	error_func(proc, strerror(errno), fd);
// }

// int cd_func(t_proc	*proc, t_env	*env, int *tmp)
// {
// 	char	*old_pwd;

// 	if (open_builtin_files(proc) == 1 || env == NULL)
// 		return (close_builtin_file(tmp), 1);
// 	if (tmp != NULL)
// 		get_pipe_io_files(proc, tmp);
// 	else
// 		get_io_files(proc);
// 	old_pwd = getcwd(NULL, 0);
// 	if (proc->args[1] == NULL)
// 		return (go_home(env, old_pwd, proc, tmp));
// 	else if (proc->nb_args > 2)
// 		return (free(old_pwd), error_func(proc, "too many arguments", tmp));
// 	else if (proc->args[1][0] == '-')
// 		return (go_to_prev(env, old_pwd, proc, tmp));
// 	if (old_pwd == NULL || env->pwd == NULL)
// 		// return (error_func(proc, strerror(errno), tmp), 
// 		cd_set_pwd(proc->args[1], env, proc, tmp);
// 	if (proc->args[1][0] != 0 && chdir(proc->args[1]) < 0)
// 		return (free(old_pwd), error_func(proc, strerror(errno), tmp));
// 	set_env_variale(env, old_pwd);
// 	return (close_fds(proc), close_builtin_file(tmp), 0);
// }

// int cd_files_handle(t_proc *proc, int *tmp)
// {
// 	if (open_builtin_files(proc) == 1)
// 		return (close_builtin_file(tmp), 1);
// 	if (tmp != NULL)
// 		get_pipe_io_files(proc, tmp);
// 	else
// 		get_io_files(proc);
// 	return (0);
// }

// char *get_pwd(t_env *env, t_proc *proc)
// {
// 	char *pwd;
// 	char *tmp;

// 	pwd = getcwd(NULL, 0);
// 	if (pwd != NULL)
// 		return (pwd);
// 	if (env->pwd == NULL)
// 		return (ft_strdup(proc->args[1]));
// 	pwd = ft_strjoin(env->pwd, "/");
// 	tmp = ft_strjoin(pwd, proc->args[1]);
// 	return (free(pwd), tmp);
// }

// void set_env_var(t_env *env, char *oldpwd, t_proc *proc)
// {
// 	t_lst *lst_pwd;
// 	t_lst *lst_old;

// 	free(env->pwd);
// 	env->pwd = get_pwd(env, proc);
// 	lst_pwd = env_search2(env, "PWD");
// 	lst_old = env_search2(env, "OLDPWD");
// 	if (lst_pwd == NULL)
// 	{
// 		remove_node(env, lst_old);
// 		free(oldpwd);
// 		return ;
// 	}
// 	free(lst_old->varible);
// 	lst_old->varible = ft_strjoin("OLD", lst_pwd->varible);
// 	free(lst_pwd->varible);
// 	lst_pwd->varible = ft_strjoin("PWD=", env->pwd);
// }

// int cd_func(t_proc *proc, t_env *env, int *tmp)
// {
// 	if (cd_files_handle(proc, tmp) == 1)
// 		return (1);
// 	if (proc->args[1] == NULL)
// 		return (go_home(env, proc, tmp));
// 	else if (proc->args[1][0] == '-')
// 		return (go_to_prev(env, proc, tmp));
// 	else if (proc->args[1][0] != 0 && chdir(proc->args[1]) < 0)
// 		return (error_func(proc, strerror(errno), tmp));
// 	set_env_var(env, proc);
// 	return (close_fds(proc), close_builtin_file(tmp), 0);
// }





















