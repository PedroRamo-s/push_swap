/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:08:39 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/13 07:01:20 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*void	reverse_rotate(t_node **stack)
{
	t_node	*first;
	t_node	*last;

	first = *stack;
	last = *stack;
	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->previous->next = NULL;
	last->next = first;
	first->previous = last;
	last->previous = NULL;
	*stack = last;
}

void	rra(t_node **stack_a)
{
	reverse_rotate(stack_a);
	ft_printf("rra\n");
}

void	rrb(t_node **stack_b)
{
	reverse_rotate(stack_b);
	ft_printf("rrb\n");
}*/

static void	reverse_rotate(t_stack *s)
{
	t_node	*last;

	if (!s || !s->top || !s->top->next)
		return ;
	last = s->bottom;
	s->bottom = last->previous;
	s->bottom->next = NULL;
	last->previous = NULL;
	last->next = s->top;
	s->top->previous = last;
	s->top = last;
}
void	rra(t_stack *a)
{
	if (!a || !a->top || !a->top->next)
		return ;
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	if (!b || !b->top || !b->top->next)
		return ;
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	int	rotated_a;
	int	rotated_b;

	rotated_a = 0;
	rotated_b = 0;
	if (a && a->top && a->top->next)
	{
		reverse_rotate(a);
		rotated_a = 1;
	}
	if (b && b->top && b->top->next)
	{
		reverse_rotate(b);
		rotated_b = 1;
	}
	if (rotated_a && rotated_b)
		write(1, "rrr\n", 4);
	else if (rotated_a)
		write(1, "rra\n", 4);
	else if (rotated_b)
		write(1, "rrb\n", 4);
}
