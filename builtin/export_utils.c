/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:18:38 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/19 11:25:32 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compar_func(const char *in_env, const char *to_find)
{
	int	i;

	i = 0;
	while (in_env[i] && to_find[i] && in_env[i] != '=')
	{
		if (in_env[i] != to_find[i])
			break ;
		i++;
	}
	if (in_env[i] == '=' && to_find[i] == '=')
		return (UPDATE);
	else if (in_env[i] == '\0' && to_find[i] == '=')
		return (UPDATE);
	else if (in_env[i] == '=' && to_find[i] == '\0')
		return (DONOTHING);
	else if (in_env[i] == '\0' && to_find[i] == '\0')
		return (DONOTHING);
	return (NOMATCH);
}

int	is_valide(const char *buffer)
{
	if (*buffer == '=' || *buffer == '\0' || ft_isdigit(*buffer))
		return (0);
	while (*buffer && is_id(*buffer))
		buffer++;
	if (*buffer == '=' || *buffer == '\0')
		return (1);
	return (0);
}

void	update_state(t_lst *lst)
{
	if (ft_strchr(lst->varible, '=') == NULL)
		lst->state = NO_VAL;
	else
		lst->state = DISPLAY;
}
