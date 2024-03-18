/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:14:42 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/18 00:56:31 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <libc.h>
// #include "tmp.h"
#include <string.h>

int error_builtin_file(void)
{
	ft_printf(2, "error opening file\n");
	return (1);
}

int open_builtin_files(t_proc	*proc)
{
	unsigned int i;

	i = 0;
	while (i < proc->nb_file)
	{
		if (proc->file[i].mod == INPUT)
			proc->file[i].fd = open(proc->file[i].file_name, O_RDONLY);
		else if (proc->file[i].mod == OUTPUT)
			proc->file[i].fd = open(proc->file[i].file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (proc->file[i].mod == APPEND)
			proc->file[i].fd = open(proc->file[i].file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (proc->file[i].fd < 0)
			return (error_builtin_file());
		i++;
	}
	return (0);
}

int count_builtins(t_proc	*proc, int size)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (ft_strcmp(proc->args[0], "echo") == 0
		|| ft_strcmp(proc->args[0], "env") == 0
		/*|| ft_strcmp(proc->args[0], "cd") == 0
		|| ft_strcmp(proc->args[0], "exit") == 0
		|| ft_strcmp(proc->args[0], "export") == 0*/
		|| ft_strcmp(proc->args[0], "pwd") == 0
		/*|| ft_strcmp(proc->args[0], "unset") == 0*/)
			count++;
		i++;
	}
	return (count);
}

int init_builtin(t_proc	*proc, t_env	*env, int *tmp)
{
	if (ft_strcmp(proc->args[0], "echo") == 0)
		return (echo_func(proc, tmp));
	else if (ft_strcmp(proc->args[0], "env") == 0)
		return (env_func(proc, env, tmp));
	// else if (ft_strcmp(proc->args[0], "cd") == 0)
	// 	return (cd_func(proc));
	// else if (ft_strcmp(proc->args[0], "unset") == 0)
	// 	return (unset_func(proc));
	// else if (ft_strcmp(proc->args[0], "export") == 0)
	// 	return (export_func(proc));
	// else if (ft_strcmp(proc->args[0], "exit") == 0)
	// 	return (exit_func(proc));
	else if (ft_strcmp(proc->args[0], "pwd") == 0)
		return (pwd_func(proc, tmp));
	return (-1);
}
// int	check_builtin(char *cmd_name)
// {
// 	char **blin;
// 	int	i;

// 	i = 0;
// 	blin = ft_split("exit env unset export pwd cd echo", ' ');
// 	while (blin[i] != NULL)
// 	{
// 		if (ft_strcmp(blin[i], cmd_name) == 0)
// 			return (free_tab(blin), 1);
// 		i++;
// 	}
// 	return(0);
// }
