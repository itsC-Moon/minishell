/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:29:46 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/21 16:00:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void minishell(const char *shell, t_env *envp)
{
	t_mini mini;
	char *buffer;
	int status = 0;

	while (1)
	{
		buffer = readline(shell);
		if (!buffer)
			break ;
		if (*shell && !is_empty(buffer))
			add_history(buffer);
		else
			continue;
		mini = parser(buffer, envp);
		if (mini.size == 0 && mini.nb_doc == 0)
			continue;
		print_mini(mini);
		mini.status = status;
		init_procs(&mini);
		status = mini.status;
	}
}
