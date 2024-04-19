/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:56 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/19 11:55:50 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int process_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WTERMSIG(status) == SIGINT)
		return (130);
	else if (WTERMSIG(status) == SIGQUIT)
		return (131);
	return (2);
}
