/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:00:00 by username          #+#    #+#             */
/*   Updated: 2026/07/02 04:50:55 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	int		integer;
	int		decimal;
	double	scaled_value;

	scaled_value = value * 100.0;
	integer = (int) scaled_value;
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
		+bench->pa + bench->pb
		+bench->ra + bench->rb + bench->rr
		+bench->rra + bench->rrb + bench->rrr);
}

void	print_bench(t_program *prog, double disorder)
{
	ft_printf("[bench] Disorder:  ");
	bench_putpercent(disorder);
	write(2, "\n", 1);
	ft_printf("[bench] Strategy:  %s ", strategy_name(prog->strategy));
	if (prog->adaptive)
		ft_printf(" / %s \n", strategy_name(prog->adaptive));
	ft_printf("[bench] Operations:   %d\n", total_ops(&prog->bench));
	ft_printf("[bench]    sa: %d   sb: %d", prog->bench.sa, prog->bench.sb);
	ft_printf("   ss: %d\n", prog->bench.ss);
	ft_printf("[bench]    pa: %d   pb: %d \n", prog->bench.pa, prog->bench.pb);
	ft_printf("[bench]    ra: %d   rb: %d", prog->bench.ra, prog->bench.rb);
	ft_printf("   rr: %d \n", prog->bench.rr);
	ft_printf("[bench]   rra: %d  rrb: %d", prog->bench.rra, prog->bench.rrb);
	ft_printf("  rrr: %d \n", prog->bench.rrr);
}
