/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:29:42 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/19 20:02:31 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_node(t_env	*env, t_lst	*lst)
{
	if (lst == NULL)
		return ;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	if (lst == env->front)
		env->front = lst->next;
	if (lst == env->back)
		env->back = lst->prev;
	free(lst->varible);
	free(lst);
}

static t_lst	*_unset(const char *buffer, t_env *env)
{
	if (is_valide(buffer) == 1)
		return (env_search2(env, buffer));
	return (NULL);
}

int	unset_func(t_proc	*proc, t_env	*env, int *fd)
{
	int		i;
	t_lst	*it;

	i = 1;
	if (open_builtin_files(proc) == 1)
		return (close_builtin_file(fd), 1);
	close_fds(proc);
	if (proc->nb_args == 0)
		return (0);
	while (proc->args[i] != NULL)
	{
		it = _unset(proc->args[i], env);
		if (it)
			remove_node(env, it);
		i++;
	}
	return (0);
}
