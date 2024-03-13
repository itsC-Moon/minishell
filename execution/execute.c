/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:31:36 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 02:47:20 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"
#include "tmp.h"
#include <libc.h>
#include <unistd.h>

void init_pipe(t_proc *proc, unsigned int size)
{
	
}

void	init_cmd(t_proc	*proc)
{
	open_files(proc);
	
}

void	init_procs(t_mini	*mini)
{
	if (mini->size == 1)
		init_cmd(mini->proc);
	else if (mini->size > 1)
		init_pipe(mini->proc, mini->size);
}
