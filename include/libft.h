/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:16:47 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/07 15:41:29 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdarg.h>
# define SKIP 2
# define LEN 0

typedef enum e_Token_Type
{
	STRING_LTR,
	PIPE,
	INPUT_redirect,
	OUTPUT_REDIRECT,
	APPEND_REDIRECT,
	HEREDOC
}	t_Token_Type;

typedef enum e_state
{
	PARSING_ERROR	= -1,
	MALLOC_ERROR	= -2,
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
	size_t	size;
}	t_Token;

t_Token		*tokenizer(const char *buffer);

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
int			ft_isdigit(char c);
int			ft_isspace(char c);
int			ft_iskey(char c);
int			is_sep(char c);
int			is_quote(char c);
int			ft_strlen(const char *buffer);

/*parsing*/
char		*get_word(const char *str);
int			quote_s(const char *str, int mod, char *buffer);
int			jump(const char *str, int *len);
int			quote_s(const char *str, int mod, char *buffer);
int			word_s(const char *str, char *buffer);
int			jump_to(const char *buffer, char quote);
int			get_args(const char *buffer, t_Token *tokens);
#endif /*LIBFT_H*/
