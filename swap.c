/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:15:36 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/23 06:00:00 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_list *s)
{
	t_node	*first;
	t_node	*second;

	if (!s || !s->head || !s->head->next)
		return ;
	first = s->head;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->previous = first;
	else
		s->tail = first;
	second->previous = NULL;
	second->next = first;
	first->previous = second;
	s->head = second;
}

void	sa(t_program *prog)
{
	if (!prog->a.head || !prog->a.head->next)
		return ;
	swap(&prog->a);
	write(1, "sa\n", 3);
	print_stacks("sa", prog);
	if (prog->bench_mode)
		prog->bench.sa++;
}

void	sb(t_program *prog)
{
	if (!prog->b.head || !prog->b.head->next)
		return ;
	swap(&prog->b);
	write(1, "sb\n", 3);
	print_stacks("sb", prog);
	if (prog->bench_mode)
		prog->bench.sb++;
}

void	ss(t_program *prog)
{
	if (!prog->a.head || !prog->a.head->next
		|| !prog->b.head || !prog->b.head->next)
		return ;
	swap(&prog->a);
	swap(&prog->b);
	write(1, "ss\n", 3);
	print_stacks("ss", prog);
	if (prog->bench_mode)
		prog->bench.ss++;
}
