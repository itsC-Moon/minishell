/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:52:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/03 00:41:00 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void    signal_ctrl_c(int sig)
{
    (void)sig;
    write(2, "\n", 1);
	
	get_status(130, SET);
	check_exit(SIGN);
	if (in_here_doc(GET) == IN)
		exit(1);
	rl_replace_line("", 0);
    rl_on_new_line();
	if (in_exec(GET) == OUT)
		rl_redisplay();
}

void signal_ignore(int sig)
{
	ft_printf(1, "Quit: 3\n");
	(void)sig;
	// signal(SIGQUIT, SIG_IGN);
}
