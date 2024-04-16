/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:23:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 20:36:37 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_env	*envp;

	(void)ac;
	(void)argv;
	if (!isatty(0))
		return (ft_printf(2, "nudejs: require a tty session\n"), 1);
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	envp = env_arr_to_lst(env);
	minishell(envp);
	clean_env(envp);
	rl_clear_history();
	return (get_status(0, GET));
}
