/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:23:52 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/26 14:59:39 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

static int compar_func(const char *in_env, const char *to_find)
{
	int i;

	i = 0;
	while (in_env[i] && to_find[i] && in_env[i] != '=')
	{
		if (in_env[i] != to_find[i])
			break;
		i++;
	}
	if (in_env[i] == '=' && to_find[i] == '=')
		return (UPDATE);
	else if (in_env[i] == '\0' && to_find[i] == '=')
		return (UPDATE);
	else if (in_env[i] == '=' && to_find[i] == '\0')
		return (DONOTHING);
	else if (in_env[i] == '\0' && to_find[i] == '\0')
		return (DONOTHING);
	return (ERROR);
}

static int is_valide(const char *buffer)
{
	if (*buffer == '=' || *buffer == '\0' || ft_isdigit(*buffer))
		return (0);
	while (*buffer && is_id(*buffer))
		buffer++;
	if (*buffer == '=' || *buffer == '\0')
		return (1);
	return (0);
}

static void __insert(t_state state, t_env *env, t_lst *tmp, const char *name)
{
	if (!tmp)
	{
		tmp = lst_addback(env->back, name);
		if (ft_strchr(tmp->varible, '=') == NULL)
			tmp->state = HIDE;
		else
			env->size++;
	}
	else if (state == UPDATE)
	{
		free(tmp->varible);
		tmp->varible = ft_strdup(name);
		if (ft_strchr(tmp->varible, '=') == NULL)
			return ;
		env->size++;
		tmp->state = DISP;
	}
}

static void insert_var(t_env *env, const char *name)
{
	t_lst *tmp;
	t_state state;

	tmp = env->front;
	while (tmp != NULL)
	{
		state = compar_func(tmp->varible, name);
		if (state == DONOTHING)
			return ;
		else if (state == UPDATE)
			break ;
		tmp = tmp->next;
	}
	__insert(state, env, tmp, name);
}

static int export_var(t_proc *proc, t_env *env)
{
	size_t i;
	int status;
	int state;

	status = 0;
	i = 0;
	while (i < proc->nb_args - 1)
	{
		state = is_valide(proc->args[i + 1]);
		if (state == 1)
			insert_var(env, proc->args[i + 1]);
		else if (state == 0)
		{
			status = 1;
			ft_printf(2, "nudejs: export: `%s': not a valid identifier\n", proc->args[i + 1]);
		}
		i++;
	}
	return (status);
}

static void print_env2(t_env *env, int fd)
{
	const t_lst *it;
	const char *it2;

	it = env->front;
	while (it)
	{
		ft_printf(fd, "declare -x ");
		it2 = it->varible;
		while (*it2 && *it2 != '=')
			write(fd, it2++, 1);
		if (*it2)
			ft_printf(fd, "=\"%s\"", it2 + 1);
		ft_printf(fd, "\n");
		it = it->next;
	}
}
int export_func(t_proc *proc, int *fd, t_env *env)
{

	if (open_builtin_files(proc) == 1)
		return (1);
	if (fd != NULL)
		get_pipe_io_files(proc, fd);
	else
		get_io_files(proc);
	if (proc->nb_args == 1)
		print_env2(env, proc->io_fd[1]);
	else
		return (export_var(proc, env));
	return (0);
}
