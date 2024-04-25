/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 03:08:51 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/21 12:28:15 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*init_pipe_struct(int size)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	check_null(pipe, "malloc");
	pipe->i = 0;
	pipe->fd[0] = 0;
	pipe->fd[1] = 0;
	pipe->tmp[0] = -1;
	pipe->tmp[1] = -1;
	pipe->pids = malloc(sizeof(int) * size);
	check_null(pipe->pids, "malloc");
	return (pipe);
}
