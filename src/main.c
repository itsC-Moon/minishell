/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:41:41 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/14 20:50:23 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main()
// {
// 	char *buffer;
// 	while ((buffer =  readline("nudejs>")) != NULL)
// 	{
// 		t_Token *token = tokenizer(buffer);
// 		free(buffer);
// 		t_list *ptr = token->front;
// 		if (!ptr)
// 			printf("syntax Error\n");
// 		while (ptr)
// 		{
// 			printf("%s -->", ptr->token);
// 			get_type(ptr->type);
// 			ptr = ptr->next;
// 		}
// 		if (token->front)
// 			free_tokens(token);
// 		free(token);
// 	}

// }
// int main(int argc, char **argv, char **envp)
// {
// 	if (argc < 1)
// 		error_exit("rak ka tkhawr", 1);
// 	t_mini mini;
// 	mini.envp = env_arr_to_lst(envp);
// 	mini.size = 1;
// 	mini.proc->args = argv;
// 	mini.proc->nb_file = 0;
// 	init_procs(&mini);
// 	printf("input --> %d\noutput --> %d", mini.proc->io_fd[0], mini.proc->io_fd[1]);
// 	exit(mini.status);
// }
