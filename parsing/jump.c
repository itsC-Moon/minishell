/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:17:05 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/21 12:33:44 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(const char *str)
{
	int		i;
	int		len;
	char	*s;

	if (!str || !*str)
		return (NULL);
	if (jump(str, &len) < 0)
		return (NULL);
	s = malloc(sizeof(char) * len + 1);
	check_null(s, "malloc");
	*s = 0;
	i = 0;
	while (str[i] && !is_sep(str[i]))
	{
		len = word_s(str + i, s + ft_strlen(s));
		len += quote_s(str + len + i, SKIP, s + ft_strlen(s));
		i += len;
	}
	return (s);
}

int	append(const char *buffer, char *new_buffer, int lock)
{
	int	j;
	int	i;

	j = ft_strlen(new_buffer);
	i = 0;
	if (buffer[i] == '"')
		i++;
	if (buffer[i] == '\'' && !lock)
		new_buffer[j++] = buffer[i++];
	while (buffer[i] && !end_var(buffer[i]))
	{
		new_buffer[j] = buffer[i];
		i++;
		j++;
	}
	new_buffer[j] = '\0';
	return (i);
}

void	copy_to_buffer(const char *buffer, char *new_buffer, t_env *envp)
{
	int		j;
	int		i;
	char	*new;

	if (buffer[0] == '?')
	{
		new = ft_itoa(get_status(0, GET));
		check_null(new, "malloc");
	}
	else
	{
		new = env_search(envp, buffer);
		if (!new)
			return ;
	}
	j = ft_strlen(new_buffer);
	i = 0;
	while (new[i])
		new_buffer[j++] = new[i++];
	new_buffer[j] = '\0';
	if (buffer[0] == '?')
		free(new);
}

int	jump_to_s(const char *str, char *new_buffer)
{
	int		i;
	int		j;

	if (new_buffer)
		j = ft_strlen(new_buffer);
	i = 1;
	while (str[i] != '\'')
	{
		if (new_buffer)
			new_buffer[j++] = str[i];
		i++;
	}
	if (new_buffer)
		new_buffer[j] = '\0';
	return (i + 1);
}
