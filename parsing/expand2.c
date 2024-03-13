/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:18:40 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/13 13:18:59 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int var_len(const char *buffer, t_env *envp)
{
	char *new;

	new = env_search(envp, buffer);
	if (!new)
		return (0);
	return (ft_strlen(new));
}

int end_var(char c)
{
	return (c == '\0' || c == '$' || is_quote(c));
}
int inc(const char *buffer)
{
	int len;

	len = 0;
	while (!is_sep(buffer[len]) && !end_var(buffer[len]))
		len++;
	return (len);
}
