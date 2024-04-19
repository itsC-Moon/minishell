/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:23:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/18 21:37:09 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static t_env *init_env(char **env)
{
	t_env *envp;

	envp = env_arr_to_lst(env);
	env_addback(envp, make_lst(ft_strdup("OLDPWD"), NO_VAL));
	return (envp);
}
void leaks()
{
	char cmd[256] = {0};
	sprintf(cmd, "lsof -p %d", getppid());
	system(cmd);
}
int	main(int ac, char **argv, char **env)
{atexit(leaks);
	t_env	*envp;

	(void)ac;
	(void)argv;
	if (!isatty(0))
		return (ft_printf(2, "nudejs: require a tty session\n"), 1);
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	envp = init_env(env);
	minishell(envp);
	clean_env(envp);
	rl_clear_history();
	return (get_status(0, GET));
}
