/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:08:32 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/21 23:54:16 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	pwd_func(t_proc	*proc, int *tmp)
{
	char *cwd;

	if (open_builtin_files(proc) == 1)
		return (1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (error("pwd"), 1);
	ft_printf(proc->io_fd[1], "%s\n", cwd);
	free(cwd);
	return (0);
}
