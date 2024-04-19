/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:10:45 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/19 19:14:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_status(int status, int opt)
{
	static int	_status;

	if (opt == GET)
		return (_status);
	_status = status;
	return (_status);
}

int	in_here_doc(int opt)
{
	static int	_in_here_doc = OUT;

	if (opt == IN)
		_in_here_doc = IN;
	else if (opt == OUT)
		_in_here_doc = OUT;
	return (_in_here_doc);
}

int	in_exec(int opt)
{
	static int	_in_exec = OUT;

	if (opt == IN)
		_in_exec = IN;
	else if (opt == OUT)
		_in_exec = OUT;
	return (_in_exec);
}

int	process_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WTERMSIG(status) == SIGINT)
		return (130);
	else if (WTERMSIG(status) == SIGQUIT)
		return (131);
	return (2);
}
