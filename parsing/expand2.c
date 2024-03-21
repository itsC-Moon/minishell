/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:18:40 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 22:02:49 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
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
	while (is_id(buffer[len]))
		len++;
	return (len);
}
static int is_valid(char c)
{

	return (c == '\0' || c == ':' || c == '/' ||
			c == '$');
}
int expand_tildes(const char *buffer, t_env *envp, char *new_buffer)
{
	int i;
	char *home;
	
	i = 0;
	if (buffer[0] != '~' || !is_valid(buffer[1]))
		return (0);
	home = env_search(envp, "HOME");
	if (!home)
	{
		if (!new_buffer)
			return (1);
		*new_buffer = '~';
		*(new_buffer + 1) = '\0';
		return (1);
	}
	if (!new_buffer)
		return (ft_strlen(home));
	while (*home)
		new_buffer[i++] = *(home++);
	new_buffer[i] = '\0';
	return (1);
}
