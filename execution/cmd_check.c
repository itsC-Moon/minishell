/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:29:41 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/27 16:27:56 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>

static int	is_dir(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

static void	exit_error(const char *str, int exit_val, const char *name, int *fd)
{
	if (fd != NULL)
	{
		close (fd[0]);
		close (fd[1]);
	}
	ft_printf(2, "nudejs: %s: %s\n", name, str);
	exit(exit_val);
}

void	check_cmd(t_proc	*proc, char *cmd, int *fd)
{
	if (ft_strchr(cmd, '/') != NULL && is_dir(cmd) == 1)
		exit_error("Is a directory", 126, proc->args[0], fd);
	else if (access(cmd, F_OK) == -1 && ft_strchr(cmd, '/') != NULL)
		exit_error("No such file or directory", 127, proc->args[0], fd);
	else if (access(cmd, X_OK) == -1 && ft_strchr(cmd, '/') != NULL)
		exit_error("Permission denied", 126, proc->args[0], fd);
	else if (access(cmd, F_OK | X_OK) == -1
		&& ft_strchr(proc->args[0], '/') == NULL)
		exit_error("command not found", 127, proc->args[0], fd);
}
