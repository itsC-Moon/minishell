/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:10:45 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/25 17:36:55 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
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

int	check_exit(int sig, int opt)
{
	static int	__signal;

	if (opt == GET)
		return (__signal);
	__signal = sig;
	return (__signal);
}

int	process_status(int status)
{
	if (check_exit(0, GET) == SIGI)
		write(2, "\n", 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WTERMSIG(status) == SIGINT)
		return (130);
	else if (WTERMSIG(status) == SIGQUIT)
	{
		ft_printf(1, "Quit :3\n");
		return (131);
	}
	return (2);
}
