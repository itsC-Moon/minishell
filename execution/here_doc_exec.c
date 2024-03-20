/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <hibenouk@1337.ma>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:29:58 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/20 01:22:04 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <sys/fcntl.h>

void read_until_lim(t_file	*here_doc)
{
	char *buff;
	int fd;

	fd = open(here_doc->file_name, O_CREAT | O_WRONLY, 0644);
	buff = NULL;
	while (1)
	{
		buff = readline(">");
		if (buff == NULL)
			return ;
		if (ft_strcmp(buff, here_doc->limiter) == 0)
			break ;
		ft_printf(fd, "%s\n", buff);
		free(buff);
	}
	close (fd);
}
void here_doc_exec(t_mini	*mini)
{
	unsigned int i;

	i = 0;
	while (i < mini->nb_doc)
	{
		read_until_lim(&(mini->here_doc[i]));	
		i++;
	}
}
