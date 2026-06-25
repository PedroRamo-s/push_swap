/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:03:11 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/23 06:00:00 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_list *src, t_list *dst)
{
	t_node	*node;

	if (!src || !src->head)
		return ;
	node = src->head;
	src->head = node->next;
	if (src->head)
		src->head->previous = NULL;
	else
		src->tail = NULL;
	src->size--;
	node->next = dst->head;
	node->previous = NULL;
	if (dst->head)
		dst->head->previous = node;
	else
		dst->tail = node;
	dst->head = node;
	dst->size++;
}

void	pa(t_program *prog)
{
	push(&prog->b, &prog->a);
	write(1, "pa\n", 3);
	print_stacks("pa", prog);
	if (prog->bench_mode)
		prog->bench.pa++;
}

void	pb(t_program *prog)
{
	push(&prog->a, &prog->b);
	write(1, "pb\n", 3);
	print_stacks("pb", prog);
	if (prog->bench_mode)
		prog->bench.pb++;
}
