/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 01:06:03 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/17 05:24:31 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*void	rotate(t_node **stack)
{
	t_node *current;
	t_node *first;
	t_node *last;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	first = *stack;
    current = *stack;
	*stack = first->next;
	(*stack)->previous = NULL;
	while ((current->next) != NULL)
	{
		current = current->next;
	}
	last = current;
	current->next = first;
	first->previous = last;
	first->next = NULL;
}

void ra(t_node **stack_a)
{
    rotate(stack_a);
    ft_printf("ra\n");
}

void rb(t_node **stack_b)
{
    rotate(stack_b);
    ft_printf("rb\n");
}*/

#include "push_swap.h"

static void	rotate(t_stack *s)
{
	t_node	*first;

	if (!s || !s->top || !s->top->next)
		return ;
	first = s->top;
	s->top = first->next;
	s->top->previous = NULL;
	first->next = NULL;
	first->previous = s->bottom;
	s->bottom->next = first;
	s->bottom = first;
}
void	ra(t_stack *a, t_stack *b, t_bench *bench)
{
	if (!a || !a->top || !a->top->next)
		return ;
	rotate(a);
	write(1, "ra\n", 3);
	print_stacks("ra", a, b);
	if (bench)
		bench -> ra++;
}

void	rb(t_stack *b, t_stack *a, t_bench *bench)
{
	if (!b || !b->top || !b->top->next)
		return ;
	rotate(b);
	write(1, "rb\n", 3);
	print_stacks("rb", a, b);
	if (bench)
		bench -> rb++;
}

void	rr(t_stack *a, t_stack *b, t_bench *bench)
{
	int	rotated_a;
	int	rotated_b;

	rotated_a = 0;
	rotated_b = 0;
	if (a && a->top && a->top->next)
	{
		rotate(a);
		rotated_a = 1;
	}
	if (b && b->top && b->top->next)
	{
		rotate(b);
		rotated_b = 1;
	}
	if (rotated_a && rotated_b)
	{
		write(1, "rr\n", 3);
		print_stacks("rr", a, b);
		if (bench)
			bench -> rr++;
	}
	else if (rotated_a)
	{
		write(1, "ra\n", 3);
		if (bench)
			bench -> ra++;
	}
	else if (rotated_b)
	{
		write(1, "rb\n", 3);
		if (bench)
			bench -> rb++;
	}
}
