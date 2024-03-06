/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:59 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/06 15:00:34 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
#include <sys/_types/_size_t.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_Token_Type
{
	COMMANDE,
	PIPE,
	INPUT_redirect,
	OUTPUT_REDIRECT,
	APPEND_REDIRECT,
	HEREDOC

}	t_Token_Type;

typedef struct  s_list
{
	char			*token;
	t_Token_Type	type;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;

typedef struct s_Token
{
	t_list	*front;
	t_list	*back;
	size_t	size;
}	t_Token;
#endif /* !MINISHELL_H */
