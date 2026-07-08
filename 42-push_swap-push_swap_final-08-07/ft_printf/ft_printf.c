/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 04:10:57 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/01 05:12:10 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_handle(char c, va_list *args, int fd)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(*args, int), fd));
	else if (c == 's')
		return (ft_putstr(va_arg(*args, char *), fd));
	else if (c == 'p')
		return (ft_putptr(va_arg(*args, void *), fd));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(*args, int), fd));
	else if (c == 'u')
		return (ft_putnbr_uns(va_arg(*args, unsigned int), fd));
	else if (c == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), 'x', fd));
	else if (c == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), 'X', fd));
	else if (c == '%')
		return (ft_putchar('%', fd));
	return (-1);
}

static int	ft_handle_percent(const char **format, va_list *args)
{
	(*format)++;
	while (**format >= '0' && **format <= '9')
		(*format)++;
	return (ft_format_handle(**format, args, 2));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		ret;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			ret = ft_handle_percent(&format, &args);
		else
			ret = write(2, format, 1);
		if (ret == -1)
			return (va_end(args), -1);
		count += ret;
		if (*format)
			format++;
	}
	va_end(args);
	return (count);
}
