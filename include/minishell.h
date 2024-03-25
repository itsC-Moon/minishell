/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:35:23 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/25 14:54:29 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# define FILE 1
# define ARGS 0
# define GET 2
# define SET 3


typedef enum e_open_type
{
	INPUT,
	OUTPUT,
	APPEND,
	_HEREDOC,
	AMBIGUOUS,
}	t_open_type;

typedef enum e_state 
{
	DONOTHING = 2,
	NOMATCH,
	INSERT ,
	UPDATE ,
	ERROR 
}	t_state;
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
	char		*limiter;
	t_open_type	mod;
}	t_file;

typedef struct s_proc
{
	t_file		*file;
	size_t		nb_file;
	int			io_fd[2];
	char		*command; // will be NULL :TODO : search inn PATH
	char		**args;
	t_open_type	type;
	size_t		nb_args;
}	t_proc;

typedef struct s_mini
{
	t_proc		*proc;
	t_env		*envp;
	size_t		size;
	int			status;
	t_file		*here_doc;
	size_t		nb_doc;
}	t_mini;

/*minishell*/
void		minishell(t_env *envp);


/*----------------EXECUTE---------------*/

/*cmd_check*/
void		check_cmd(t_proc	*proc, char *cmd, int *fd);

/*env_2d2lst*/
t_env		*env_arr_to_lst(char **envp);
char **env_lst_to_arr(t_env *env);
t_lst *lst_addback(t_lst	*lst, const char *to_add);

/*env_search*/
char		*env_search(t_env	*env, const char *name);
t_lst		*env_search_2(t_env	*env, const char *name);
char		*env_search_3(t_env	*env, const char *name);

/*execute*/
void		close_fds(t_proc	*proc);
void		init_procs(t_mini	*mini);

/*files_handle*/
void open_files(t_proc	*proc);
void		get_io_files(t_proc	*proc);
void		get_pipe_io_files(t_proc	*proc, int *fd);

/*here_doc_exec*/
void		here_doc_exec(t_mini	*mini);

/*path_handle*/
char *get_cmd_path(t_proc	*proc, t_env *env);

/*pipe*/
int			init_pipe(t_proc *proc, unsigned int size, t_env *envp, int mini_status);

/*-----------------EXECUTE--------------*/

/*-----------------BUILTIN--------------*/

/*builtin*/
int			open_builtin_files(t_proc	*proc);
void		close_builtin_file(int *tmp);
int			init_builtin(t_proc	*proc, t_env *env, int *tmp, int status);

/*cd_func*/
int 		cd_func(t_proc	*proc, t_env	*env, int *tmp);

/*echo*/
int			echo_func(t_proc	*proc, int *tmp, int status);

/*env_func*/
int 		env_func(t_proc	*proc, t_env	*env, int *tmp);

/*exit_func*/
int			exit_func(t_proc	*proc, int *tmp);

/*export_func*/
int			export_func(t_proc	*proc, int *fd, t_env *env);

/*pwd_func*/
int			pwd_func(t_proc	*proc, int *tmp);

/*unset_func*/
int 		unset_func(t_proc	*proc, t_env	*env, int *fd);

/*-----------------BUILTIN--------------*/

/*expand*/
char		*expand(const char *buffer, t_env *envp, int opt);
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


/*here_doc*/
void		init_here_doc(t_mini *mini);

void print_tokens(t_Token *tokens);
/*clean*/
void		clean_mini(t_mini *mini);
void		free_env(t_env *envp);

/*static */
int			get_status(int status, int opt);

/*debug*/
void print2d(char **argv, size_t size);
void print_mini(t_mini mini);
void print_file(t_file *file, size_t size);
void leaks();
#endif /* !MINISHELL_H */
