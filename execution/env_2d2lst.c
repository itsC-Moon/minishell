/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2d2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:32:40 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/23 15:50:21 by hibenouk         ###   ########.fr       */
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
	return (tmp->next);
}

t_env	*env_arr_to_lst(char **envp)
{
	t_env	*env;
	t_lst	*lst;
	int		i;
	t_lst	*tmp;

	i = 0;
	lst = malloc(sizeof(t_lst));
	check_null(lst, "malloc");
	env = malloc(sizeof(t_env));
	check_null(env, "malloc");
	lst->varible = ft_strdup(envp[i++]);
	lst->next = NULL;
	lst->prev = NULL;
	while (envp[i] != NULL)
		tmp = lst_addback(lst, envp[i++]);
	env->back = tmp;
	env->front = lst;
	env->size = i;
	return (env);
}

char **env_lst_to_arr(t_env *env)
{
	t_lst *lst = env->front;
	char **arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(char *) * (env->size + 1));
	if (arr == NULL)
		exit (1);
	while (lst != NULL)
	{
		arr[i] = ft_strdup(lst->varible);
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

