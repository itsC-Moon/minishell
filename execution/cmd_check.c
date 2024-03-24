/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:42:08 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/22 22:04:31 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int is_dir(char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

static void exit_error(const char *str, int exit_val, const char *name)
{
	ft_printf(2, "nudejs: %s: %s\n",name, str);
	exit(exit_val);
}

void	check_cmd(t_proc	*proc, char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL && is_dir(cmd) == 1)
		exit_error("is a directory", 126, cmd);
	else if (access(cmd, F_OK) == -1 && ft_strchr(cmd, '/') != NULL)
		exit_error("No such file or directory", 1, cmd);
	else if (access(cmd, F_OK | X_OK) == -1 && ft_strchr(proc->args[0], '/') == NULL)
		exit_error("command not found", 127, cmd);
	else if (access(cmd, X_OK) == -1 && ft_strchr(cmd, '/') != NULL)
		exit_error("permission denied", 126, cmd);
}


