/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:32:40 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/27 14:54:24 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"


t_env	*env_arr_to_lst(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = make_env();
	if(!*envp)
		return (env);
	while (envp[i] != NULL)
		env_addback(env, make_lst(ft_strdup(envp[i++]), DISP));
	return (env);
}

char **env_lst_to_arr(t_env *env)
{
	t_lst	*lst;
	char	**arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(char *) * (env->dis_size + 1));
	check_null(arr, "malloc");
	lst = env->front;
	while (lst)
	{
		if (lst->state == DISP)
			arr[i++] = ft_strdup(lst->varible);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

