/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:41:10 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 23:56:33 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft.h"
#include "tmp.h"

int	check_builtin(char *cmd_name)
{
	char **blin;
	int	i;

	i = 0;
	blin = ft_split("exit env unset export pwd cd echo", ' ');
	while (blin[i] != NULL)
	{
		if (ft_strcmp(blin[i], cmd_name) == 0)
			return (free_tab(blin), 1);
		i++;
	}
	return(0);
}

