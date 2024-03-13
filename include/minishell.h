/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:42:32 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 21:42:33 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
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

// typedef enum e_proc_type
// {
	// BIULTEIN,
	// REDIRECTION,
	// COMMAND,
	// HERE_DOC,
// }	t_proc_type;

typedef struct s_lst
{
	char			*varible;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_env
{
	t_lst	*front;
	t_lst	*back;
	size_t	size;
}	t_env;

typedef struct s_file
{
	char		*file_name;
	int			fd;
	t_open_type	mod;
}	t_file;

typedef struct s_proc
{
	t_file		*file;
	size_t		nb_file;
	char		*command; // will be NULL :TODO : search inn PATH
	char		**args;
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
	t_env		*envp;
	size_t		size;
	t_here_doc	*here_doc;
}	t_mini;
/*expand*/
char		*expand(const char *buffer, t_env *envp);
void		copy_to_buffer(const char *buffer, char *new_buffer, t_env *envp);
int			var_len(const char *buffer, t_env *envp);
int			end_var(char c);
int			inc(const char *buffer);

/*parsing*/
t_Token		*tokenizer(const char *buffer);
size_t		count_command(t_Token *token);
size_t		get_num_redic(t_list *list);
/*constructor*/
t_file		*file(char *file_name, t_open_type mod);

/*env */
char		*env_search(t_env	*env, const char *name);
t_env		*env_arr_to_lst(char **envp);
void		check_cmd(t_proc	*proc, char *cmd);
#endif /* !MINISHELL_H */
