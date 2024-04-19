/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:23:52 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/19 11:27:58 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_insert(t_state state, t_env *env, t_lst *it, const char *name)
{
	if (!it)
	{
		env_addback(env, make_lst(ft_strdup(name), NO_VAL));
		env->back->state = DISPLAY;
		env->dis_size++;
		update_state(env->back);
	}
	else if (state == UPDATE)
	{
		free(it->varible);
		it->varible = ft_strdup(name);
		env->size++;
		update_state(it);
	}
}

static void	insert_var(t_env *env, const char *name)
{
	t_lst	*it;
	t_state	state;

	it = env->front;
	while (it != NULL)
	{
		state = compar_func(it->varible, name);
		if (state == DONOTHING)
			return ;
		else if (state == UPDATE)
			break ;
		it = it->next;
	}
	_insert(state, env, it, name);
}

static int	export_var(t_proc *proc, t_env *env)
{
	size_t	i;
	int		status;
	int		state;

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
			ft_printf(2, "nudejs: export: `%s': not a valid identifier\n",
				proc->args[i + 1]);
		}
		i++;
	}
	return (status);
}

static void	print_env2(t_env *env, int fd)
{
	t_lst	*it;
	char	*it2;

	it = env->front;
	while (it)
	{
		if (it->state == DEF_PATH)
		{
			it = it->next;
			continue ;
		}
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

int	export_func(t_proc *proc, int *fd, t_env *env)
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
