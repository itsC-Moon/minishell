/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:31:19 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 13:03:19 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int is_id(const char c)
{
	return (c == '_' || ft_isalpha(c) || ft_isdigit(c));
}
char *env_search(t_env	*env, const char *name)
{
	t_lst	*tmp;
	int i;

	tmp = env->front;
	if (!is_id(name[0]))
		return ("$");
	while(tmp != NULL)
	{
		i = 0;
		while (tmp->varible[i] == name[i] && is_id(name[i]))
			i++;
		if (tmp->varible[i] == '=' && !is_id(name[i]))
			return (tmp->varible + i + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

