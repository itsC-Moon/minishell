/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:08:32 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/23 01:50:57 by zkotbi           ###   ########.fr       */
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
		return (close_fds(proc), error("pwd"), 1);
	ft_printf(proc->io_fd[1], "%s\n", cwd);
	free(cwd);
	close_fds(proc);
	return (close_builtin_file(tmp), 0);
}
