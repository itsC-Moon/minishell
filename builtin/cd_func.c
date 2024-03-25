/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:57:48 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/25 20:33:48 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static int error_func(t_proc *proc, char *str, int *tmp)
{
	close_builtin_file(tmp);
	close_fds(proc);
	ft_printf(2, "nudejs: %s: %s \n", proc->args[0], str);	
	return (1);
}

static void	set_env_variale(t_env *env, char *old_pwd)
{
	t_lst *lst;

	lst = env_search_2(env, "OLDPWD");
	if (lst != NULL)
	{
		free(lst->varible);
		lst->varible = ft_strjoin("OLDPWD=", old_pwd);
		free(old_pwd);
	}
	lst = env_search_2(env, "PWD");
	if (lst != NULL)
	{
		free(lst->varible);
		old_pwd = getcwd(NULL, 0);
		lst->varible = ft_strjoin("PWD=", old_pwd);
		free(old_pwd);
	}

}

static int go_home(t_env *env, char *old_pwd, t_proc *proc, int *tmp)
{
	char *home;

	home = env_search(env, "HOME");
	if (home == NULL)
		return (free(old_pwd), error_func(proc, "HOME not set", tmp));
	if (chdir(home) < 0)
		return (free(old_pwd), error_func(proc, strerror(errno), tmp));
	set_env_variale(env, old_pwd);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

static int go_to_prev(t_env *env, char *old_pwd, t_proc *proc, int *tmp)
{
	char *pwdold_var;

	pwdold_var = env_search(env, "OLDPWD");
	if (pwdold_var == NULL)
		return (free(old_pwd), error_func(proc, "OLDPWD not set", tmp));
	if (pwdold_var[0] == 0)
		return (free(old_pwd), 0); 
	if (chdir(pwdold_var) < 0)
		return (free(old_pwd), error_func(proc, strerror(errno), tmp));
	ft_printf(proc->io_fd[1], "%s\n", pwdold_var);
	set_env_variale(env, old_pwd);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}

int cd_func(t_proc	*proc, t_env	*env, int *tmp)
{
	char	*old_pwd;

	if (open_builtin_files(proc) == 1 || env == NULL)
		return (close_builtin_file(tmp), 1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	old_pwd = getcwd(NULL, 0);
	if (proc->args[1] == NULL)
		return (go_home(env, old_pwd, proc, tmp));
	else if (proc->nb_args > 2)
		return (free(old_pwd), error_func(proc, "too many arguments", tmp));
	else if (proc->args[1][0] == '-')
		return (go_to_prev(env, old_pwd, proc, tmp));
	if (proc->args[1][0] != 0 && chdir(proc->args[1]) < 0)
		return (free(old_pwd), error_func(proc, strerror(errno), tmp));
	set_env_variale(env, old_pwd);
	return (close_fds(proc), close_builtin_file(tmp), 0);
}
// 	lst = env_search_2(env, "OLDPWD");
// 	if (lst != NULL)
// 	{
// 		free(lst->varible);
// 		lst->varible = ft_strjoin("OLDPWD=", old_pwd);
// 		free(old_pwd);
// 	}
// 	lst = env_search_2(env, "PWD");
// 	if (lst != NULL)
// 	{
// 		free(lst->varible);
// 		old_pwd = getcwd(NULL, 0);
// 		lst->varible = ft_strjoin("PWD=", old_pwd);
// 		free(old_pwd);
// 	}
// }	
