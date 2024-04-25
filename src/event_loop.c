/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:33:26 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/25 17:40:59 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	execute(t_mini *mini)
{
	init_procs(mini);
	get_status(mini->status, SET);
	clean_mini(mini);
}

void	minishell(t_env *envp)
{
	char			*buffer;
	t_mini			mini;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		check_exit(NORM, SET);
		buffer = readline("nudejs>$ ");
		if (!buffer)
			return ;
		if (is_empty(buffer))
		{
			free(buffer);
			continue ;
		}
		add_history(buffer);
		mini = parser(buffer, envp);
		free(buffer);
		if (mini.size == 0 && mini.nb_doc == 0)
			continue ;
		execute(&mini);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}
