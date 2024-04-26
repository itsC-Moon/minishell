/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:23:16 by zkotbi            #+#    #+#             */
/*   Updated: 2024/04/26 09:59:02 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_to_file(int fd, const char *buffer,
		t_env *envp, t_open_type state)
{
	int		i;
	char	*var;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$' && state != NO_EXPAND)
		{
			var = env_search(envp, buffer + i + 1);
			buffer += inc(buffer + i + 1) + 1;
			if (!var)
				continue ;
			ft_printf(fd, "%s", var);
		}
		else
			ft_printf(fd, "%c", buffer[i++]);
	}
	ft_printf(fd, "\n");
	return (0);
}

static int	read_until_lim(t_file	*here_doc, t_env *envp)
{
	char	*buffer;
	int		fd;

	fd = open(here_doc->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (1);
	buffer = NULL;
	while (1)
	{
		buffer = readline(">");
		if (buffer == NULL)
			break ;
		if (ft_strcmp(buffer, here_doc->limiter) == 0)
			break ;
		print_to_file(fd, buffer, envp, here_doc->state);
		free(buffer);
	}
	free(buffer);
	close (fd);
	return (0);
}

static void	here_doc_exec(t_mini	*mini)
{
	size_t	i;

	i = 0;
	in_here_doc(IN);
	while (i < mini->nb_doc)
	{
		if (read_until_lim(&(mini->here_doc[i]), mini->envp) == 1)
			break ;
		i++;
	}
	in_here_doc(OUT);
	exit(0);
}

int	fork_here_doc(t_mini	*mini)
{
	int		pid;
	int		status;

	if (mini->nb_doc == 0)
		return (0);
	pid = fork();
	if (pid == 0)
		here_doc_exec(mini);
	waitpid(pid, &status, 0);
	mini->status = WEXITSTATUS(status);
	get_status(mini->status, SET);
	if (mini->status == 0)
		return (0);
	mini->status = 130;
	get_status(mini->status, SET);
	return (1);
}
