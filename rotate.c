/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 01:06:03 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/23 06:00:00 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_list *s)
{
	t_node	*first;

	if (!s || !s->head || !s->head->next)
		return ;
	first = s->head;
	s->head = first->next;
	s->head->previous = NULL;
	first->previous = s->tail;
	s->tail->next = first;
	first->next = NULL;
	s->tail = first;
}

void	ra(t_program *prog)
{
	if (!prog->a.head || !prog->a.head->next)
		return ;
	rotate(&prog->a);
	write(1, "ra\n", 3);
	print_stacks("ra", prog);
	if (prog->bench_mode)
		prog->bench.ra++;
}

void	rb(t_program *prog)
{
	if (!prog->b.head || !prog->b.head->next)
		return ;
	rotate(&prog->b);
	write(1, "rb\n", 3);
	print_stacks("rb", prog);
	if (prog->bench_mode)
		prog->bench.rb++;
}

void	rr(t_program *prog)
{
	if (!prog->a.head || !prog->a.head->next
		|| !prog->b.head || !prog->b.head->next)
		return ;
	rotate(&prog->a);
	rotate(&prog->b);
	write(1, "rr\n", 3);
	print_stacks("rr", prog);
	if (prog->bench_mode)
		prog->bench.rr++;
}
