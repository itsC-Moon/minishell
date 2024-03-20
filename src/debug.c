/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:02:37 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/20 15:44:14 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
void get_type(t_Token_Type type) {
  switch (type) {
    case STRING_LTR:
      printf("STRING_LTR\n");
      break;
    case PIPE:
      printf("PIPE\n");
      break;
    case INPUT_REDIR:
      printf("INPUT_REDIR\n");
      break;
    case OUTPUT_REDIR:
      printf("OUTPUT_REDIR\n");
      break;
    case APPEND_REDIR:
      printf("APPEND_REDIR\n");
      break;
    case HEREDOC:
      printf("HEREDOC\n");
      break;
  };
}

void print2d(char **argv, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		printf("|%s| ",argv[i]);
		i++;
	}
	printf("\n");
}
void print_file(t_file *file, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		printf("%s =>",file[i].file_name);
		if (file[i].mod == INPUT)
			printf("INPUT\n");
		else if (file[i].mod == APPEND)
			printf("APPEND\n");
		else if (file[i].mod == OUTPUT)
			printf("OUTPUT\n");
		else if (file[i].mod == _HEREDOC)
			printf("limiter=> %s| _HEREDO\n",file[i].limiter);
		++i;
	}
}
void print_mini(t_mini mini)
{
	t_proc *it;

	it =mini.proc;
	size_t i = 0;
	print_file(mini.here_doc, mini.nb_doc);
	printf("------------------------\n");
	while (i < mini.size)
	{
		print2d(it[i].args, it[i].nb_args);
		print_file(it[i].file, it[i].nb_file);
		i++;
	}
}

void print_tokens(t_Token *tokens)
{
	t_list *it;

	it = tokens->front;
	while (it)
	{
		if (it->type ==PIPE)
			ft_printf(2, "PIPE");
		else
		{
			ft_printf(2, "%s ",it->token);
			get_type(it->type);
		}
		it = it->next;
	}
}
