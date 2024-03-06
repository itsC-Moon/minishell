/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:16:47 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/06 14:55:05 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdarg.h>
/*Error*/
void	error(const char *name);
/*printf*/
int			ft_printf(int fd, const char *str, ...);
int			ft_putstr(int fd, const char *str);
int			ft_putnbr(int fd, int n);
int			ft_puthex(int fd, int n, const char *base);
int			ft_putnbr_u(int fd, unsigned int n);
int			ft_putaddr(int fd, void *ptr);
#endif /*LIBFT_H*/
