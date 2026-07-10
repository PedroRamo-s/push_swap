/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 03:26:19 by aantela-          #+#    #+#             */
/*   Updated: 2026/05/24 21:27:04 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_uns(unsigned int n, int fd)
{
	int		len;
	char	c;

	len = 0;
	if (n >= 10)
		len += ft_putnbr_uns(n / 10, fd);
	c = (n % 10) + '0';
	len += ft_putchar(c, fd);
	return (len);
}
