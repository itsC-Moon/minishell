/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <student.h42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:43:03 by zkotbi            #+#    #+#             */
/*   Updated: 2024/03/13 21:43:22 by zkotbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# define SKIP 2
# define LEN 0
/*debug*/
# define STR(x) dprintf(2, "%s->%s\n",#x,x);
# define INT(x) dprintf(2, "%s->%d\n",#x,x);
# define CHAR(x) dprintf(2, "%s->%c\n",#x,x);
# define INFO(x) dprintf(2, "%s->line=%d file%s\n",x,__LINE__, __FILE__)


typedef enum e_Token_Type
{
	STRING_LTR,
	PIPE,
	INPUT_REDIR,
	OUTPUT_REDIR,
	APPEND_REDIR,
	HEREDOC,
}	t_Token_Type;

typedef enum e_state
{
	UNC_QUOTE	= -1,
	UNE_EOF	= -1,
	NO_ERROR		= -3
}	t_state;


typedef struct s_list
{
	char			*token;
	t_Token_Type	type;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_Token
{
	t_list	*front;
	t_list	*back;
	t_state	state;
	size_t	size;
}	t_Token;

/*debug*/
void get_type(t_Token_Type type);

/*list*/
t_Token		*create_list(void);
t_list		*lst(char *token, t_Token_Type token_type);
void		addfront(t_Token *token, t_list *list);
void		addback(t_Token *token, t_list *list);

/*Error*/
void		error(const char *name);
void		error_exit(const char *name, int code);
void		check_null(const void *ptr, const char *str);

/*printf*/
int			ft_printf(int fd, const char *str, ...);
int			ft_putstr(int fd, const char *str);
int			ft_putnbr(int fd, int n);
int			ft_puthex(int fd, int n, const char *base);
int			ft_putnbr_u(int fd, unsigned int n);
int			ft_putaddr(int fd, void *ptr);

/*libft*/
int			cmp(const char *s1, const char *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(char c);
int			ft_isspace(char c);
int			ft_iskey(char c);
int			is_sep(char c);
int			is_quote(char c);
int			ft_strlen(const char *buffer);
void		free_tab(char **tab); // free 2d array
char		*ft_strchr(const char	*s, int c);
char		**ft_split(char *s, char c);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char const *s1, char const *s2);

/*parsing*/
char		*get_word(const char *str);
int			jump(const char *str, int *len);
int			quote_s(const char *str, int mod, char *buffer);
int			word_s(const char *str, char *buffer);
int			jump_to(const char *str, char *buffer);
int			jump_to_s(const char *str, char *new_buffer);
int			get_args(const char *buffer, t_Token *tokens, int (*func)(char));
char		**split_arg(const char *str);
/*free*/
void		free_list(t_list *list);
void		free_tokens(t_Token *token);

int			jump2(const char *str, int *len);
int			quote_s2(const char *str, int mod, char *buffer);
int			word_s2(const char *str, char *buffer);

#endif /*LIBFT_H*/
