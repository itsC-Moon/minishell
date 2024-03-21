/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:30:29 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 22:12:52 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell(const char *shell, t_env *envp)
{
	t_mini mini;
	char *buffer;

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
		init_procs(&mini);
	}
}
