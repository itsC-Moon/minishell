/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:57:48 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/23 21:11:55 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libc.h>


int error_func(char *name, int code)
{
	ft_printf(2, "nudejs: %s: %s\n", name, strerror(errno));	
	return (code);
}

int error_home(char *name, char *str, int code)
{
	ft_printf(2, "nudejs: %s: %s \n", name, str);	
	return (code);
}

int go_home(t_env *env)
{
	char *home;

	home = env_search(env, "HOME");
	if (home == NULL)
		return (error_home("cd", "HOME not set",  1));
	if (chdir(home) < 0)
		return (error_func("cd", 1));
	return (0);
}

int go_to_prev(t_env *env)
{
}

int cd_func(t_proc	*proc, t_env	*env, int *tmp)
{
	t_lst	*lst;
	char	*old_pwd;
	
	close_builtin_file(tmp);
	if (open_builtin_files(proc) == 1 || env == NULL)
		return (1);
	close_fds(proc);
	old_pwd = getcwd(NULL, 0);
	if (proc->args[1] == NULL)
		return (free(old_pwd), go_home(env));
	else if (proc->nb_args > 2)
		return (free(old_pwd), error_home("cd", "too many arguments", 1));
	else if (proc->args[1][0] == '-')
		return (free(old_pwd), go_to_prev(env));
	if (chdir(proc->args[1]) < 0)
		return (free(old_pwd), error_func("cd", 1));
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
	return (0);
}	

