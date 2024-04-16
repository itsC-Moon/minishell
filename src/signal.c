/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:52:33 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 18:22:53 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_ctrl_c(int sig)
{
    (void) sig;
    write(2, "\n", 1);

    check_exit(SIGI, SET);
    get_status(130, SET);
    if (in_here_doc(GET) == IN)
    {
        exit(1);
    }
    rl_replace_line("", 0);
    rl_on_new_line();
    if (in_exec(GET) == OUT)
    {
        rl_redisplay();
    }
}

void signal_ignore(int sig)
{
    (void) sig;
    check_exit(SIGQ, SET);
    get_status(131, SET);
    ft_printf(1, "Quit: 3\n");
}
