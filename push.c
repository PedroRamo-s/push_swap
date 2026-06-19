/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:03:11 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/17 05:15:07 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack *src, t_stack *dst)
{
	t_node	*node;

	if (!src || !src->top)
		return ;
	node = src->top;
	src->top = node->next;
	if (src->top)
		src->top->previous = NULL;
	else
		src->bottom = NULL;
	src->size--;
	node->next = dst->top;
	node->previous = NULL;
	if (dst->top)
		dst->top->previous = node;
	else
		dst->bottom = node;
	dst->top = node;
	dst->size++;
}

void	pa(t_stack *a, t_stack *b, t_bench *bench)
{
	push(b, a);
	write(1, "pa\n", 3);
	print_stacks("pa", a, b);
	if (bench)
		bench -> pa++;
}

void	pb(t_stack *a, t_stack *b, t_bench *bench)
{
	push(a, b);
	write(1, "pb\n", 3);
	print_stacks("pb", a, b);
	if (bench)
		bench -> pb++;
}
