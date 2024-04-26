/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:52:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/26 10:01:46 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrl_c(int sig)
{
	(void)sig;
	if (in_exec(GET) == IN)
		check_exit(SIGI, SET);
	if (in_exec(GET) == OUT)
		write(2, "\n", 1);
	get_status(130, SET);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (in_exec(GET) == OUT)
		rl_redisplay();
}


void	signal_ctrl_doc(int sig)
{
	(void)sig;
	if (in_exec(GET) == IN)
		check_exit(SIGI, SET);
	if (in_exec(GET) == OUT)
		write(2, "\n", 1);
	get_status(130, SET);
	if (in_here_doc(GET) == IN)
		exit(1);
	rl_replace_line("", 0);
	rl_on_new_line();
}
void	signal_ignore(int sig)
{
	(void)sig;
	get_status(131, SET);
	check_exit(SIGQ, SET);
}
