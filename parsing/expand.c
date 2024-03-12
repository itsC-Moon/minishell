/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:56:14 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/11 19:04:01 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>

char **get_args2(const char *buffer)
{
	(void)buffer;
	return (NULL);
}
// TODO : zaid 
int var_len(const char *buffer)
{
	if (!buffer[1])
		return (1);
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
	return (len + 1);
}

int	jump_to_s(const char *str, char *new_buffer)
{
	int		i;

	if (new_buffer)
		new_buffer[0] = '\'';
	i = 1;
	while (str[i] != '\'')
	{
		if (new_buffer)
			new_buffer[i] = str[i];
		i++;
	}
	if (new_buffer)
	{
		new_buffer[i] = str[i];
		new_buffer[i + 1] = '\0';
	}
	return (i + 1);
}



int get_expand_len(const char *buffer)
{
	int		i;
	int		len;
	int		lock_d;


	i = 0;
	len = 0;
	lock_d = 1;
	while (buffer[i])
	{
		if (buffer[i] == '"')
			lock_d = (lock_d != 1);
		if (lock_d && buffer[i] == '\'')
			i += jump_to_s(buffer + i, NULL);
		else if (buffer[i] == '$')
		{
			len += var_len(buffer + i);
			buffer += inc(buffer + i + 1);
		}
		else
			i++;
	}
	return (i + len);
}
void copy_to_buffer(const char *buffer, char *new_buffer)
{
	(void)buffer;
	(void)new_buffer;
}

int append(const char *buffer, char *new_buffer)
{
	int		j;
	int		i;

	j = ft_strlen(new_buffer);
	i = 0;
	while (buffer[i] == ' ' || !end_var(buffer[i]))
	{
		new_buffer[j] = buffer[i];
		i++;
		j++;
	}
	new_buffer[j] = '\0';
	return (i);
}

char *expand(const char *buffer)
{
	int		i;
	int		lock_d;
	char	*new_buffer = malloc(100);


	i = 0;
	lock_d = 1;
	while (buffer[i])
	{
		if (buffer[i] == '"')
			lock_d = (lock_d != 1);
		if (lock_d && buffer[i] == '\'')
			i += jump_to_s(buffer + i, new_buffer);
		else if (buffer[i] == '$')
		{
			copy_to_buffer(buffer + i, new_buffer);
			buffer += inc(buffer + i + 1);
		}
		else
			i += append(buffer + i, new_buffer);
	}
	return (new_buffer);
}
int main(int argc, char *argv[])
{
	// char *buffer;
	// while ((buffer = readline("nudejs>$ ")) != NULL)
	// {
	// 	STR(buffer);
	// 	int len  =get_expand_len(buffer);
	// 	INT(len)
	// }
	const char *buffer = "\"$PWD\"world";
	// STR(buffer);
	int len  = get_expand_len(buffer);
	INT(len)

	return EXIT_SUCCESS;
}
