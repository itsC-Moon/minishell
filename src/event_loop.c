/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:30:29 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 13:49:15 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell(t_env *envp)
{
	t_mini mini;
	char *buffer;

	while (1)
	{
		buffer = readline("nudejs>$ ");
		if (!buffer)
			break ;
		if (!is_empty(buffer))
			add_history(buffer);
		else
			continue;
		mini = parser(buffer, envp);
		// printf("%d\n",a);
	}
}
