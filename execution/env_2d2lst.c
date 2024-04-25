/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:21:47 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/21 12:24:34 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_env	*env_null_def(t_env	*env)
{
	char	*def_path;

	def_path = "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.";
	if (env->pwd != NULL)
		env_addback(env, make_lst(ft_strjoin("PWD=", env->pwd), DISPLAY));
	env_addback(env, make_lst(ft_strdup(def_path), DEF_PATH));
	return (env);
}

t_env	*env_arr_to_lst(char **envp)
{
	t_env	*env;
	int		i;
	t_lst	*lst;
	char	*tmp;
	char	*def_path;

	def_path = "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.";
	i = 0;
	env = make_env();
	env->pwd = set_pwd();
	if (!*envp)
		return (env_null_def(env));
	while (envp[i] != NULL)
		env_addback(env, make_lst(ft_strdup(envp[i++]), DISPLAY));
	lst = env_search2(env, "PWD");
	if (lst != NULL && env->pwd != NULL)
	{
		free(lst->varible);
		tmp = ft_strdup(env->pwd);
		lst->varible = ft_strjoin("PWD=", tmp);
		free(tmp);
	}
	if (env_search2(env, "PATH") == NULL)
		env_addback(env, make_lst(ft_strdup(def_path), DEF_PATH));
	return (env);
}

char	**env_lst_to_arr(t_env *env)
{
	t_lst	*lst;
	char	**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * (env->dis_size + 1));
	check_null(arr, "malloc");
	lst = env->front;
	while (lst)
	{
		if (lst->state == DISPLAY)
			arr[i++] = ft_strdup(lst->varible);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}
