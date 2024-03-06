/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:16:47 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/06 18:11:39 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdarg.h>
/*list*/

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
/*list*/
t_Token		*create_list();
t_list		*lst(char *token, t_Token_Type token_type);
void		addfront(t_Token *token, t_list *list);
void		addback(t_Token *token, t_list *list);

/*Error*/
void	error(const char *name);
/*printf*/
int			ft_printf(int fd, const char *str, ...);
int			ft_putstr(int fd, const char *str);
int			ft_putnbr(int fd, int n);
int			ft_puthex(int fd, int n, const char *base);
int			ft_putnbr_u(int fd, unsigned int n);
int			ft_putaddr(int fd, void *ptr);
/*libft*/
int		cmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_isprint(char c);
int		ft_isascii(char c);
#endif /*LIBFT_H*/
