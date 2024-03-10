/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:56:14 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/10 18:53:21 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>

char **get_args2(const char *buffer)
{
	(void)buffer;
	return (NULL);
}
// TODO : zaid 
int var_len(const char *buffer)
{
	(void)buffer;
	return (0);
}

int end_var(char c)
{
	return (c == '\0' || c == '$' || is_sep(c) || c == '"');
}
int inc(const char *buffer)
{
	int len;

	len = 0;
	while (!end_var(buffer[len]))
		len++;
	return (len);
}

int	jump_to(const char *str, char *buffer)
{
	int		i;
	char	quote;

	i = 0;
	quote = (*str == '\'') * '\'' + (*str == '"') * '"';
	if (buffer)
		*buffer++ = *(str++);
	while (str[i] != quote)
	{
		if (buffer)
			buffer[i] = str[i];
		i++;
	}
	if (buffer)
	{
		buffer[i] = quote;
		buffer[i] = '\0';
	}
	return (i);
}

int get_expand_len(const char *buffer)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	char new_buffer[1024] = {0};
	while (buffer[i])
	{
		if (buffer[i] == '\'')
			i += jump_to(buffer + i, NULL);
		if (buffer[i] == '$')
			buffer += inc(buffer + i + 1) + 1;
		else
		{
			new_buffer[i] = buffer[i];
			i++;
		}
	}
	int len2 = strlen(new_buffer);
	STR(new_buffer)
	INT(len2)
	return (i + len);
}
// char *expand(char *buffer)
// {
// 	int		lock;
// 	int		i;

// 	i = 0;
// 	lock = 1;
// 	while (buffer[i])
// 	{
// 		if (lock && buffer[i] == '$')
// 			
// 	}
// }
int main(int argc, char *argv[])
{
	// char *buffer;
	// while ((buffer = readline("nudejs>$ ")) != NULL)
	// {
	// 	STR(buffer);
	// 	int len  =get_expand_len(buffer);
	// }
	const char *buffer = "'$hello' world";
	STR(buffer);
	get_expand_len(buffer);

	return EXIT_SUCCESS;
}
