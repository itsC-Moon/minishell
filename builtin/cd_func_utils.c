/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:54:14 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/19 11:38:09 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	*get_pwd(t_env *env, t_proc *proc)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		ft_printf(2, "cd: error retrieving current director\n");
	if (pwd != NULL)
		return (pwd);
	if (env->pwd == NULL)
		return (ft_strdup(proc->args[1]));
	pwd = ft_strjoin(env->pwd, "/");
	tmp = ft_strjoin(pwd, proc->args[1]);
	return (free(pwd), tmp);
}

static void	_utils(t_env *env, t_lst	*lst_pwd, t_lst	*lst_old)
{
	if (lst_pwd == NULL)
	{
		env_addback(env, make_lst(ft_strjoin("PWD=", env->pwd), HIDE));
		if (lst_old == NULL)
			env_addback(env, make_lst(ft_strdup("OLDPWD="), HIDE));
		else
		{
			free(lst_old->varible);
			lst_old->varible = ft_strdup("OLDPWD=");
		}
	}
	else
	{
		if (lst_old == NULL)
			env_addback(env,
				make_lst(ft_strjoin("OLD", lst_pwd->varible), HIDE));
		else
		{
			free(lst_old->varible);
			lst_old->varible = ft_strjoin("OLD", lst_pwd->varible);
		}
		free(lst_pwd->varible);
		lst_pwd->varible = ft_strjoin("PWD=", env->pwd);
	}
}

void	set_env_vars(t_env *env, t_proc *proc)
{
	t_lst	*lst_pwd;
	t_lst	*lst_old;
	char	*tmp;

	tmp = get_pwd(env, proc);
	free(env->pwd);
	env->pwd = tmp;
	lst_pwd = env_search2(env, "PWD");
	lst_old = env_search2(env, "OLDPWD");
	_utils(env, lst_pwd, lst_old);
}
