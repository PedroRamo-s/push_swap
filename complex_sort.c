/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:39:42 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/27 06:11:37 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//roda ate o minimo ficar por no head
static void	rotate_min_to_top(t_program *prog)
{
	t_node	*min;
	int		pos;
	int		cost;

	min = stack_min(&prog->a);
	pos = get_pos(&prog->a, min);
	cost = signed_cost(pos, prog->a.size);
	while (cost > 0)
	{
		ra(prog);
		cost--;
	}
	while (cost < 0)
	{
		rra(prog);
		cost++;
	}
}

static void		push_all_to_b(t_program *prog)
{
	while (prog->a.size > 3)
		pb(prog);
}

void	complex_sort(t_program *prog)
{
	push_all_to_b(prog);
	sort_three(prog);
	while (prog->b.size > 0)
		move_cheapest(prog);
	rotate_min_to_top(prog);
}

