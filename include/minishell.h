/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:59:59 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/19 12:35:06 by hibenouk         ###   ########.fr       */
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
	_HEREDOC,
}	t_open_type;

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
	char		*limiter;
	t_open_type	mod;
}	t_file;

typedef struct s_proc
{
	t_file	*file;
	size_t	nb_file;
	char	*command;
	char	**args;
	size_t	nb_args;
}	t_proc;

typedef struct s_mini
{
	t_proc		*proc;
	t_env		*envp;
	size_t		size;
	t_file		*here_doc;
	size_t		nb_doc;
}	t_mini;
/*expand*/
char		*expand(const char *buffer, t_env *envp);
int			expand_tildes(const char *buffer, t_env *envp, char *new_buffer);
void		copy_to_buffer(const char *buffer, char *new_buffer, t_env *envp);
int			var_len(const char *buffer, t_env *envp);
int			end_var(char c);
int			inc(const char *buffer);

/*parsing*/
t_Token		*tokenizer(const char *buffer);
t_mini		parser(const char *buffer, t_env *envp);
size_t		count_command(t_Token *token);
size_t		get_num_redic(t_list *list, t_Token_Type type);
/*constructor*/
t_file		file(char *file_name, t_open_type mod);
t_file		file_here(char *limiter, t_open_type mod);

/*env */
char		*env_search(t_env	*env, const char *name);
t_env		*env_arr_to_lst(char **envp);
void		check_cmd(t_proc	*proc, char *cmd);

/*debug*/

void print2d(char **argv, size_t size);
void print_mini(t_mini mini);
void print_file(t_file *file, size_t size);
#endif /* !MINISHELL_H */
