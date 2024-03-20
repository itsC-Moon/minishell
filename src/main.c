/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:41:41 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 13:47:21 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

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
	// int		status;

	envp = env_arr_to_lst(env);
	signal(SIGINT, ft_signal_ctrl_c);
	// char *path = env_search(envp, "PATH");
	minishell(envp);

	// char *str = remove_quote("'file '' name'");
	// STR(str)
	// const char *buffer = "cat << 'lp' <<ppo";
	// t_mini mini = parser(buffer, envp);
	// print_mini(mini);
	// mini.proc[3];
	return (0);
}
