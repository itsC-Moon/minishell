/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:06:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/22 00:45:13 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
# include <fcntl.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

void    ft_signal_ctrl_c(int sig)
{
    (void)sig;
    write(2, "\n", 1);
	rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void leaks()
{
	system("leaks minishell");
}

int main(int ac, char **argv, char **env)
{/*atexit(leaks);*/

	(void)ac;
	(void)argv;
	t_env	*envp;

	if (!isatty(0))
		return (ft_printf(2, "nudejs: require a tty session\n"), 1);
	envp = env_arr_to_lst(env);
	signal(SIGINT, ft_signal_ctrl_c);
	minishell(envp);
	free_env(envp);
	rl_clear_history();
	return (0);
}
