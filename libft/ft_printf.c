/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:35:51 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/24 21:18:21 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handler(int fd, va_list ap, char format)
{
	int	count;
	int	c;

	count = 0;
	if (format == 'd' || format == 'i')
		count = ft_putnbr(fd, va_arg(ap, int));
	else if (format == 'u')
		count = ft_putnbr_u(fd, va_arg(ap, int));
	if (format == 'x')
		count = ft_puthex(fd, va_arg(ap, int), "0123456789abcdef");
	else if (format == 'X')
		count = ft_puthex(fd, va_arg(ap, int), "0123456789ABCDEF");
	else if (format == 'p')
		count = ft_putaddr(fd, va_arg(ap, void *));
	if (format == 's')
		count = ft_putstr(fd, va_arg(ap, char *));
	else if (format == 'c')
		(1 == 1) && (c = va_arg(ap, int), count = write(fd, &c, 1));
	return (count);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	ap;
	int		count;
	int		curr;

	if (write(fd, &count, 0) < 0)
		return (-1);
	va_start(ap, str);
	count = 0;
	while (*str != '\0')
	{
		curr = 0;
		if (*str == '%' && *(++str))
			curr = ft_handler(fd, ap, *str);
		else if (*str)
			curr = write(fd, str, 1);
		if (curr <= -1)
			return (va_end(ap), -1);
		count += curr;
		if (*str != '\0')
			str++;
	}
	va_end(ap);
	return (count);
}
