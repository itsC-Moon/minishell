/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:29:41 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 21:41:39 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <sys/fcntl.h>
#include "../include/minishell.h"
#include "tmp.h"

void open_files(t_proc	*proc)
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
		i++;
	}
}
