/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:06:25 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 22:08:11 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
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
{

	(void)ac;
	(void)argv;
	(void)env;
	t_env	*envp;
	char *shell;
	// int		status;

	shell = "";
	if (isatty(0))
		shell = "nudejs>$ ";
	envp = env_arr_to_lst(env);
	signal(SIGINT, ft_signal_ctrl_c);
	minishell(shell, envp);

	return (0);
}
