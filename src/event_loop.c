/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:33:26 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/16 20:35:08 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <termios.h>

static void	execute(t_mini *mini)
{
	signal(SIGQUIT, signal_ignore);
	init_procs(mini);
	signal(SIGQUIT, SIG_IGN);
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
		get_status(mini.status, SET);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}
