/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:15:36 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/13 06:59:02 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *s)
{
	t_node	*first;
	t_node	*second;

	if (!s || !s->top || !s->top->next)
		return ;
	first = s->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->previous = first;
	else
		s->bottom = first;
	second->previous = NULL;
	second->next = first;
	first->previous = second;
	s->top = second;
}

void	sa(t_stack *a)
{
	if (!a || !a->top || !a->top->next)
		return ;
	swap(a);
	write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	if (!b || !b->top || !b->top->next)
		return ;
	swap(b);
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	int	swapped_a;
	int	swapped_b;

	swapped_a = 0;
	swapped_b = 0;
	if (a && a->top && a->top->next)
	{
		swap(a);
		swapped_a = 1;
	}
	if (b && b->top && b->top->next)
	{
		swap(b);
		swapped_b = 1;
	}
	if (swapped_a && swapped_b)
		write(1, "ss\n", 3);
	else if (swapped_a)
		write(1, "sa\n", 3);
	else if (swapped_b)
		write(1, "sb\n", 3);
}
