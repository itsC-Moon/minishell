/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:59 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/10 19:07:59 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_open_type
{
	INPUT,
	OUTPUT,
	APPEND,
}	t_open_type;

typedef struct s_file
{
	char		*file_name;
	t_open_type	mod;
}	t_file;

typedef struct s_proc
{
	t_file	*file;
	size_t	nb_file;
	char	*command; // will be NULL :TODO : search inn PATH
	char	**args;
}	t_proc;

typedef struct s_here_doc
{
	char		*file_name;
	char		*limiter;
	size_t		nb_doc;
}	t_here_doc;

typedef struct s_mini
{
	t_proc		*proc;
	size_t		size;
	t_here_doc	*here_doc;
}	t_mini;

t_Token		*tokenizer(const char *buffer);
size_t		count_command(t_Token *token);
size_t		get_num_redic(t_list *list);
/*constructor*/
t_file *file(char *file_name, t_open_type mod);
#endif /* !MINISHELL_H */
