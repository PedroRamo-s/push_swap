/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:00:00 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/01 05:17:39 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	bench_putstr(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
}

static void	bench_putint(int n)
{
	char	buf[12];
	int		i;
	int		neg;

	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	i = 11;
	buf[i] = '\0';
	if (n == 0)
		buf[--i] = '0';
	while (n > 0)
	{
		buf[--i] = '0' + (n % 10);
		n /= 10;
	}
	if (neg)
		buf[--i] = '-';
	write(2, buf + i, 11 - i);
}

static void	bench_putpercent(double value)
{
	int	integer;
	int	decimal;
	double scaled_value;

	scaled_value = value *100.0;
	integer = (int)scaled_value;
	decimal = (int)((scaled_value - integer) * 100.0 + 0.05);
	if (decimal >= 100)
	{
		integer += 1;
		decimal = 0;
	}
	bench_putint(integer);
	write(2, ".", 1);
	if (decimal < 10)
		write(2, "0", 1);
	bench_putint(decimal);
	write(2, "%", 1);
}

static int	total_ops(t_bench *bench)
{
	return (bench->sa + bench->sb + bench->ss
		+ bench->pa + bench->pb
		+ bench->ra + bench->rb + bench->rr
		+ bench->rra + bench->rrb + bench->rrr);
}

void	print_bench_operations(t_program *prog)
{
	ft_printf("[bench] Operations:   %d\n",total_ops(&prog->bench));
	ft_printf("[bench]   sa: %d sb: %d", prog->bench.sa, prog->bench.sb);
	ft_printf(" ss: %d\n",prog->bench.ss);
	bench_putstr("[bench]   pa: ");
	bench_putint(prog->bench.pa);
	bench_putstr("   pb: ");
	bench_putint(prog->bench.pb);
	write(2, "\n", 1);
	bench_putstr("[bench]   ra: ");
	bench_putint(prog->bench.ra);
	bench_putstr("   rb: ");
	bench_putint(prog->bench.rb);
	bench_putstr("   rr: ");
	bench_putint(prog->bench.rr);
	write(2, "\n", 1);
	bench_putstr("[bench]   rra: ");
	bench_putint(prog->bench.rra);
	bench_putstr("  rrb: ");
	bench_putint(prog->bench.rrb);
	bench_putstr("  rrr: ");
	bench_putint(prog->bench.rrr);
	write(2, "\n", 1);
}
void	print_bench(t_program *prog, double disorder)
{
	ft_printf("[bench] Disorder:    ");
	bench_putpercent(disorder);
	write(2, "\n", 1);
	ft_printf("[bench] Strategy:  %s ", strategy_name(prog->strategy));
	if (prog->adaptive)
		ft_printf(" / %s \n", strategy_name(prog->adaptive));
	print_bench_operations(prog);
}
