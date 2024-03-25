/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:23:16 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/24 21:25:11 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print_to_file(int fd, const char *buffer, t_env *envp)
{
	int		i;
	char	*var;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$')
		{	
			var = env_search(envp, buffer + i + 1);
			buffer += inc(buffer + i + 1) + 1;
			if (!var)
				continue;
			if (ft_printf(fd, "%s", var) < 0)
				return (-1);
			continue;
		}
		ft_printf(fd, "%c", buffer[i]);
		i++;
	}
	ft_printf(fd, "\n");
	return (0);
}

static int read_until_lim(t_file	*here_doc, t_env *envp)
{
	char *buff;
	int fd;

	fd = open(here_doc->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (1);
	buff = NULL;
	while (1)
	{
		buff = readline(">");
		if (buff == NULL)
			return (close(fd), 0);
		if (ft_strcmp(buff, here_doc->limiter) == 0)
			break ;
		print_to_file(fd, buff, envp);
		free(buff);
	}
	free(buff);
	close (fd);
	return (0);
}

void here_doc_exec(t_mini	*mini)
{
	size_t i;

	i = 0;
	while (i < mini->nb_doc)
	{
		if (read_until_lim(&(mini->here_doc[i]), mini->envp) == 1)
			return ;
		i++;
	}
}
