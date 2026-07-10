/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 04:07:46 by aantela-          #+#    #+#             */
/*   Updated: 2026/05/24 23:15:42 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c, int fd);
int	ft_putstr(char *c, int fd);
int	ft_putnbr(int n, int fd);
int	ft_puthex(unsigned long n, char t, int fd);
int	ft_putptr(void	*ptr, int fd);
int	ft_putnbr_uns(unsigned int n, int fd);

#endif
