/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibenouk <hibenouk@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:10:23 by hibenouk          #+#    #+#             */
/*   Updated: 2024/04/16 20:55:57 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(size_t nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*random_name(size_t n)
{
	char	*result;
	int		len;
	long	nb;

	nb = n;
	len = count_numbers(nb);
	result = malloc(sizeof(char) * len + 1);
	check_null(result, "malloc");
	if (nb == 0)
		result[0] = '0';
	result[len] = '\0';
	while (nb)
	{
		result[--len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (result);
}

int	count_numbers2(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	nb;

	nb = n;
	len = count_numbers2(nb);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		result[0] = '0';
	result[len] = '\0';
	while (nb)
	{
		result[--len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (result);
}
