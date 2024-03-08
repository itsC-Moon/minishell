/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:41:41 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/08 19:32:07 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
int main()
{
	char *buffer;
	while ((buffer =  readline("nudejs>")) != NULL)
	{
		t_Token *token = tokenizer(buffer);
		t_list *ptr = token->front;
		if (!ptr)
			printf("syntax Error\n");
		while (ptr)
		{
			printf("%s -->", ptr->token);
			get_type(ptr->type);
			ptr = ptr->next;
		}
	}

}
