/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:21:47 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/18 18:56:08 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_env	*env_null_def(t_env	*env)
{
	env_addback(env, make_lst(ft_strdup("OLDPWD"), NO_VAL));
	if (env->pwd != NULL)
		env_addback(env, make_lst(ft_strjoin("PWD=", env->pwd), DISPLAY));
	env_addback(env, make_lst(
			ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."),
			DEF_PATH));
	return (env);
}

t_env	*env_arr_to_lst(char **envp)
{
	t_env	*env;
	int		i;
	t_lst	*lst;
	char	*tmp;

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
		env_addback(env, make_lst(
				ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."),
				DEF_PATH));
	return (remove_node(env, env_search2(env, "OLDPWD")), env);
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
