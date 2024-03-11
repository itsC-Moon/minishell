/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:56:14 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/11 16:45:45 by hibenouk         ###   ########.fr       */
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
	return (len);
}

int	jump_to_s(const char *str)
{
	int		i;

	i = 1;
	while (str[i] != '\'')
		i++;
	return (i + 1);
}

int	jump_to_d(const char *str)
{
	int		i;
	int		len;

	i = 1;
	len = 0;
	while (str[i] != '"')
	{
		if (str[i] == '$')	
		{
			len += var_len(str + i);
			str += inc(str + i + 1) + 1;
		}
		else
			i++;
	}
	STR(str + i + 1)
	return (i + 1);
}

int get_expand_len(const char *buffer)
{
	int		i;
	int		len;
	int		lock_d;
	int		lock_s;

	i = 0;
	len = 0;
	lock_d = 1;
	lock_s = 1;
	while (buffer[i])
	{
		if (lock_s && buffer[i] == '"')
			lock_d = (lock_d != 0);
		else if (lock_d && buffer[i] == '\'')
			i += jump_to_s(buffer + i);
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
	const char *buffer = "'$hello' \"$ANA\" world";
	STR(buffer);
	int len  = get_expand_len(buffer);
	INT(len)

	return EXIT_SUCCESS;
}
