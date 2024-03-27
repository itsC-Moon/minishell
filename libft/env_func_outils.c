/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:37:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/27 14:50:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
# include "minishell.h"

t_env *make_env()
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	check_null(env, "malloc");
	env->back = NULL;
	env->front = NULL;
	env->size = 0;
	return (env);
}

t_lst *make_lst(char *var, t_state state)
{
	t_lst *list;

	list = malloc(sizeof(t_lst));
	check_null(list, "malloc");
	list->next = NULL;
	list->prev = NULL;
	list->varible = var;
	list->state = state;
	return (list);
}

void env_addfront(t_env *env, t_lst *lst)
{
	if (env->size == 0)
	{
		env->front = lst;
		env->back = lst;
		env->size = 1;
		env->dis_size = 0;
		if (lst->state == DISP)
			env->dis_size = 1;
		return;
	}
	lst->next = env->front;
	env->front->prev = lst;
	env->front = lst;
	env->size += 1;
	if (lst->state == DISP)
		env->dis_size += 1;
}

void env_addback(t_env *env, t_lst *lst)
{
	if (env->size == 0)
	{
		env->front = lst;
		env->back = lst;
		env->size = 1;
		env->dis_size = 0;
		if (lst->state == DISP)
			env->dis_size = 1;
		return;
	}
	lst->prev = env->back;
	env->back->next = lst;
	env->back = lst;
	env->size += 1;
	if (lst->state == DISP)
		env->dis_size += 1;
}
