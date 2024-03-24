/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:28:20 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/23 23:23:39 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"
#include "minishell.h"

int is_id(char c)
{
	return (c == '_' || ft_isalpha(c) || ft_isdigit(c));
}

int validate_name(const char *name)
{
	int i = 0;
	while (name[i] != 0 && is_id(name[i]))
		i++;
	if (name[i] != 0)
		return (1);
	return (0);
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


char *env_search_3(t_env	*env, const char *name)
{
	t_lst	*tmp;
	int i;

	tmp = env->front;
	if (validate_name(name) == 1)
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

t_lst		*env_search_2(t_env	*env, const char *name)
{
	t_lst	*tmp;
	int i;

	tmp = env->front;
	while(tmp != NULL)
	{
		i = 0;
		while (tmp->varible[i] == name[i] && name[i] != 0)
			i++;
		if (tmp->varible[i] == '=' && name[i] == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

