/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:31:19 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/12 13:14:03 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*env_search(t_env	*env, char *name)
{
	t_lst	*tmp;
	int i;

	tmp = env->front;
	while(tmp != NULL)
	{
		i = 0;
		while (tmp->varible[i] == name[i] &&
			((name[i] >= '0' && name[i] <= '9')
			|| (name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= 'a' && name[i] <= 'z')))
			i++;
		if (tmp->varible[i] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

