/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:00:00 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/24 21:18:20 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Escreve uma string para stderr.
*/
static void	bench_putstr(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
}

/*
** Escreve um inteiro para stderr.
*/
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

/*
** Escreve o disorder em percentagem com 2 casas decimais para stderr.
** Exemplo: 34.07%
*/
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

/*
** Calcula o disorder da stack antes do sort.
** Conta inversoes (pares i,j onde i<j mas a[i]>a[j])
** e devolve a percentagem sobre o total de pares possivel.
*/
/*double	compute_disorder(t_list *a)
{
	t_node	*i;
	t_node	*j;
	double	mistakes;
	double	total_pairs;

	if (!a || a->size < 2)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	i = a->head;
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	return (mistakes / total_pairs * 100.0);
}*/

/*
** Calcula o total de operacoes a partir do t_bench.
*/
static int	total_ops(t_bench *bench)
{
	return (bench->sa + bench->sb + bench->ss
		+ bench->pa + bench->pb
		+ bench->ra + bench->rb + bench->rr
		+ bench->rra + bench->rrb + bench->rrr);
}

/*
** Devolve a string da estrategia e complexidade.
*/
const char	*strategy_name(t_strategy strategy)
{
	if (strategy == STRAT_SIMPLE)
		return ("simple [O(n²)]");
	if (strategy == STRAT_MEDIUM)
		return ("medium [O(n\\sqrt{n})]");
	if (strategy == STRAT_COMPLEX)
		return ("complex [O(n log n)]");
	return ("adaptive");
}

/*
** Imprime o relatorio de benchmark para stderr.
** Chamada no main apos o sort, so se config.bench_mode == 1.
*/
void	print_bench(t_program *prog, double disorder)
{
	bench_putstr("[bench] Disorder:    ");
	bench_putpercent(disorder);
	write(2, "\n", 1);
	bench_putstr("[bench] Strategy:    ");
	bench_putstr(strategy_name(prog->strategy));
	write(2, "\n", 1);
	bench_putstr("[bench] Operations:  ");
	bench_putint(total_ops(&prog->bench));
	write(2, "\n", 1);
	bench_putstr("[bench]   sa: ");
	bench_putint(prog->bench.sa);
	bench_putstr("   sb: ");
	bench_putint(prog->bench.sb);
	bench_putstr("   ss: ");
	bench_putint(prog->bench.ss);
	write(2, "\n", 1);
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
