/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:08:32 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/20 23:24:50 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	pwd_func(t_proc	*proc, int *tmp)
{
	if (open_builtin_files(proc) == 1)
		return (1);
	if (tmp != NULL)
		get_pipe_io_files(proc, tmp);
	else
		get_io_files(proc);
	ft_printf(proc->io_fd[1], "%s\n", getcwd(NULL, 0));
	return (0);
}
