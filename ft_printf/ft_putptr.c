/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 04:49:37 by aantela-          #+#    #+#             */
/*   Updated: 2026/05/24 21:27:34 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void	*ptr, int fd)
{
	int	len;

	if (!ptr)
		return (ft_putstr("(nil)", fd));
	len = 0;
	len = len + ft_putstr("0x", fd);
	len = len + ft_puthex((unsigned long)ptr, 'x', fd);
	return (len);
}
