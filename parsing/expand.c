/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:02:29 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 14:19:43 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>


int get_expand_len(const char *buffer, t_env *envp)
{
	int i;
	int len;
	int lock_d;

	i = 0;
	len = expand_tildes(buffer, envp, NULL);
	lock_d = 1;
	while (buffer[i])
	{
		if (buffer[i] == '"')
			lock_d = (lock_d != 1);
		if (lock_d && buffer[i] == '\'')
			i += jump_to_s(buffer + i, NULL);
		else if (buffer[i] == '$')
		{
			len += var_len(buffer + i + 1, envp);
			buffer += inc(buffer + i + 1) + 1;
		}
		else
			i++;
	}
	return (i + len);
}
int append(const char *buffer, char *new_buffer, int lock)
{
	int j;
	int i;

	j = strlen(new_buffer);
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

char *expand(const char *buffer, t_env *envp)
{
	int i;
	int lock_d;
	char *new_buffer;

	i = 0;
	lock_d = 1;
	new_buffer = malloc((get_expand_len(buffer, envp) + 1) * sizeof(char));
	check_null(new_buffer, "malloc");
	*new_buffer = '\0';
	buffer += expand_tildes(buffer, envp, new_buffer);
	while (buffer[i])
	{
		if (buffer[i] == '"')
			lock_d = (lock_d != 1);
		if (lock_d && buffer[i] == '\'')
			i += jump_to_s(buffer + i, new_buffer);
		else if (buffer[i] == '$')
		{
			copy_to_buffer(buffer + i + 1, new_buffer, envp);
			buffer += inc(buffer + i + 1) + 1;
		}
		i += append(buffer + i, new_buffer, lock_d);
	}
	return (new_buffer);
}

char **get_args2(const char *buffer, t_env *envp)
{
	char *str;
	char **strs;

	str = expand(buffer, envp);
	strs = split_arg(str);
	return (strs);
}
// int main(int ac, char **argv, char **env)
// {
// 	(void)ac;
// 	(void)argv;

// 	t_env	*envp = env_arr_to_lst(env);
// 	// char *buffer;
// 	// while ((buffer = readline("nudejs>$ ")) != NULL)
// 	// {
// 	// 	char *new = expand(buffer, envp);
// 	// 	STR(new);
// 	// }
// 	const char *buffer = "$HOME 'ANA'";
// 	// char *new = expand(buffer, envp);
// 	char **strs = get_args2(buffer, envp);
// 	// char **strs = split_arg(buffer);
// 	while (*strs)
// 	{
// 		STR(*strs)
// 		strs++;
// 	}
// 	return EXIT_SUCCESS;
// }

