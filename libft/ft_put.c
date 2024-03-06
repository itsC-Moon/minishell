/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:34:13 by hibenouk          #+#    #+#             */
/*   Updated: 2024/03/06 15:21:47 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(int fd, const char *str)
{
	int	i;

	if (!str)
		return (write(fd, "", 0));
	i = 0;
	while (str[i])
		i++;
	return (write(fd, str, i));
}

int	ft_putnbr(int fd, int n)
{
	char	buffer[12];
	long	nb;
	int		i;

	i = 10;
	buffer[11] = '\0';
	nb = n;
	if (n == 0)
		return (ft_putstr(fd, "0"));
	else if (nb < 0)
		nb = nb * -1;
	while (nb != 0)
	{
		buffer[i] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		buffer[i] = '-';
	else
		i++;
	return (ft_putstr(fd, buffer + i));
}

int	ft_putnbr_u(int fd, unsigned int n)
{
	char	buffer[12];
	int		i;

	i = 10;
	buffer[11] = '\0';
	if (n == 0)
		return (ft_putstr(fd, "0"));
	while (n != 0)
	{
		buffer[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	i++;
	return (ft_putstr(fd, buffer + i));
}

int	ft_puthex(int fd, int n, const char *base)
{
	unsigned int	nb;
	char			buffer[32];
	int				i;

	if (n == 0)
		return (ft_putstr(fd, "0"));
	nb = n;
	buffer[31] = '\0';
	i = 30;
	while (nb != 0)
	{
		buffer[i] = base[nb % 16];
		nb = nb / 16;
		i--;
	}
	i++;
	return (ft_putstr(fd, buffer + i));
}

int	ft_putaddr(int fd, void *ptr)
{
	size_t	addr;
	char	buffer[32];
	int		i;
	char	*base;

	addr = (size_t)ptr;
	if (addr == 0)
		return (ft_putstr(fd, "0x0"));
	base = "0123456789abcdef";
	buffer[31] = '\0';
	i = 30;
	while (addr != 0)
	{
		buffer[i] = base[addr % 16];
		addr = addr / 16;
		i--;
	}
	buffer[i--] = 'x';
	buffer[i] = '0';
	return (ft_putstr(fd, buffer + i));
}
