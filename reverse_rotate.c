/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:08:39 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/23 06:00:00 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_list *s)
{
	t_node	*last;

	if (!s || !s->head || !s->head->next)
		return ;
	last = s->tail;
	s->tail = last->previous;
	s->tail->next = NULL;
	last->next = s->head;
	s->head->previous = last;
	s->head = last;
	last->previous = NULL;
}

void	rra(t_program *prog)
{
	if (!prog->a.head || !prog->a.head->next)
		return ;
	reverse_rotate(&prog->a);
	write(1, "rra\n", 4);
	print_stacks("rra", prog);
	if (prog->bench_mode)
		prog->bench.rra++;
}

void	rrb(t_program *prog)
{
	if (!prog->b.head || !prog->b.head->next)
		return ;
	reverse_rotate(&prog->b);
	write(1, "rrb\n", 4);
	print_stacks("rrb", prog);
	if (prog->bench_mode)
		prog->bench.rrb++;
}

void	rrr(t_program *prog)
{
	if (!prog->a.head || !prog->a.head->next
		|| !prog->b.head || !prog->b.head->next)
		return ;
	reverse_rotate(&prog->a);
	reverse_rotate(&prog->b);
	write(1, "rrr\n", 4);
	print_stacks("rrr", prog);
	if (prog->bench_mode)
		prog->bench.rrr++;
}
