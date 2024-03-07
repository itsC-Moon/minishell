/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:17:05 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/07 15:19:23 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int quote_s(const char *str, int mod, char *buffer)
{
	int i;
	char quote;

	i = 0;
	quote = (*str == '\'') * '\'' + (*str == '"') * '"';
	if (quote == 0)
		return (0);
	str++;
	while (str[i] && str[i] != quote)
	{
		if (buffer)
			buffer[i] = str[i];
		i++;
	}
	if (!str[i])
		return (-1);
	if (buffer)
		buffer[i] = '\0';
	return (i + mod);
}

