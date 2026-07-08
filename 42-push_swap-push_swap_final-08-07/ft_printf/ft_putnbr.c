/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 03:50:16 by aantela-          #+#    #+#             */
/*   Updated: 2026/05/24 21:26:28 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, int fd)
{
	int		len;
	char	c;

	len = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648", fd));
	if (n < 0)
	{
		len += ft_putchar('-', fd);
		n = -n;
	}
	if (n >= 10)
		len += ft_putnbr(n / 10, fd);
	c = (n % 10) + '0';
	len += ft_putchar(c, fd);
	return (len);
}
