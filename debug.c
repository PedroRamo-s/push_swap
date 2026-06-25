/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:00:00 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/23 06:00:00 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_stack_line(const char *label, t_list *s)
{
	t_node	*cur;
	char	buf[16];
	int		i;
	long	n;
	int		neg;

	dprintf(2, "  %s (%d): ", label, s->size);
	if (!s->head)
	{
		dprintf(2, "(vazia)\n");
		return ;
	}
	cur = s->head;
	while (cur)
	{
		n = cur->value;
		neg = 0;
		if (n < 0)
		{
			neg = 1;
			n = -n;
		}
		i = 15;
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
		dprintf(2, "%s", buf + i);
		if (cur->next)
			dprintf(2, " | ");
		cur = cur->next;
	}
	dprintf(2, "\n");
}

void	print_stacks(const char *op, const t_program *prog)
{
	if (!prog)
	{
		dprintf(2, "[Debug Error]: Programa não inicializado.\n");
		return ;
	}
	dprintf(2, "\n  [%s]\n", op);
	print_stack_line("A", (t_list *)&prog->a);
	print_stack_line("B", (t_list *)&prog->b);
	dprintf(2, "  ─────────────────────\n");
}
