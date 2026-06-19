/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:00:00 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/17 04:30:47 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Apenas para debug — remover antes de entregar.
** Redireciona para stderr para não poluir o stdout (onde vão os moves).
**
** Uso:
**     print_stacks("pb", a, b);
**
** Exemplo de output:
**
**   [pb]
**   A (4): 3 | 1 | 2 | 4
**   B (1): 5
**   ─────────────────────
*/

static void	print_stack_line(const char *label, t_stack *s)
{
	t_node	*cur;
	char	buf[16];
	int		i;
	long	n;
	int		neg;

	dprintf(2, "  %s (%d): ", label, s->size);
	if (!s->top)
	{
		dprintf(2, "(vazia)\n");
		return ;
	}
	cur = s->top;
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

void	print_stacks(const char *op, t_stack *a, t_stack *b)
{
	dprintf(2, "\n  [%s]\n", op);
	print_stack_line("A", a);
	print_stack_line("B", b);
	dprintf(2, "  ─────────────────────\n");
}
