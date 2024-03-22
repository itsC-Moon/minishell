/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:52:42 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/22 00:52:43 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"

void minishell(t_env *envp)
{
	t_mini mini;
	char *buffer;
	int status = 0;

	while (1)
	{
		buffer = readline("nudejs>$ ");
		if (!buffer)
			return ;
		if (!is_empty(buffer))
			add_history(buffer);
		else
			continue;
		mini = parser(buffer, envp);
		free(buffer);
		if (mini.size == 0 && mini.nb_doc == 0)
			continue;
		mini.status = status;
		init_procs(&mini);
		// print_mini(mini);
		status = mini.status;
		// clean_mini(&mini);
	}
}
