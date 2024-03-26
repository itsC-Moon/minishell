/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:23:52 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/25 22:25:12 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_lst		*find_var(t_env	*env, const char *name)
{
	t_lst	*tmp;
	int		i;

	tmp = env->front;
	while(tmp != NULL)
	{
		i = 0;
		while (tmp->varible[i] == name[i] && name[i] != '=')
			i++;
		if (tmp->varible[i] == '=' && name[i] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	printf("%s\n",in_env + i);
	printf("%s\n",to_find + i);
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
	if (*buffer == '=' || ft_isdigit(*buffer))
		return (0);
	while (*buffer && is_id(*buffer))
		buffer++;
	if (*buffer == '=' || *buffer == '\0')
		return (1);
	return (0);
}

static void new_var(const char *buffer, t_env *env)
{
	t_lst	*ptr;

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
	if (!tmp)
	{
		printf("INSERT");
		lst_addback(env->back, name);
		env->size++;
	}
	else if (state == UPDATE)
	{
		printf("UPDATE");
		free(tmp->varible);
		tmp->varible = ft_strdup(name);
	}

}

static int export_var(t_proc *proc, t_env *env)
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
			new_var(proc->args[i + 1], env);
		else if (state == 0)
		{
			status = 1;
			ft_printf(2, "nudejs: export: `%s': not a valid identifier\n",\
					proc->args[i + 1]);
		}
		i++;
	}
	return (status);
}

static void print_env2(t_env *env, int fd)
{
	const t_lst *it;
	const char	*it2;

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
int export_func(t_proc	*proc, int *fd, t_env *env)
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
