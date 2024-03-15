/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:42:08 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 21:42:09 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int is_dir(char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

void exit_error(char *str, int exit_val)
{
	int i;

	i = 0;
	while (str[i] != 0)
		write(1, &str[i++], 1);
	write(1, "\n", 1);
	exit(exit_val);
}

void	check_cmd(t_proc	*proc, char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL && is_dir(cmd) == 1)
		exit_error("is a directory", 126);
	else if (access(cmd, F_OK) == -1 && ft_strchr(cmd, '/') != NULL)
		exit_error("No such a file or directory", 1);
	else if (access(cmd, F_OK | X_OK) == -1 && ft_strchr(proc->args[0], '/') == NULL)
		exit_error("command not found", 127);
	else if (access(cmd, X_OK) == -1 && ft_strchr(cmd, '/') != NULL)
		exit_error("permission denied", 126);
}


