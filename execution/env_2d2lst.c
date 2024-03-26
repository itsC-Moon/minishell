/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:32:40 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/26 14:55:29 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_lst *lst_addback(t_lst	*lst, const char *to_add)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_lst));
	check_null(tmp->next, "malloc");
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
	tmp->next->varible = ft_strdup(to_add);
	tmp->next->state = DISP;
	return (tmp->next);
}

t_env *new_env()
{

	t_env	*env;
	env = malloc(sizeof(t_env));
	check_null(env, "malloc");
	env->back = NULL;
	env->front = NULL;
	env->size = 0;
	return (env);
}
t_env	*env_arr_to_lst(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = new_env();
	if(!*envp)
		return (env);
	env->back = malloc(sizeof(t_lst));
	check_null(env->back, "malloc");
	env->back->state = DISP;
	env->back->varible = ft_strdup(envp[i++]);
	env->back->next	= NULL;
	env->back->prev = NULL;
	env->front = env->back;
	while (envp[i] != NULL)
		lst_addback(env->back, envp[i++]);
	env->size = i;
	return (env);
}

char **env_lst_to_arr(t_env *env)
{
	t_lst	*lst;
	char	**arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(char *) * (env->size + 1));
	check_null(arr, "malloc");
	lst = env->front;
	while (lst != NULL)
	{
		if (lst->state == DISP)
			arr[i++] = ft_strdup(lst->varible);
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

