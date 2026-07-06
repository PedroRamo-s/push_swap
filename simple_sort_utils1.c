/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:19:39 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/06 15:32:01 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_direction(int pos, int size)
{
	if (pos <= size / 2)
		return (0);
	return (1);
}

static int	get_move_cost(t_move_plan *plan)
{
	if (plan->direction_a == plan->direction_b)
	{
		if (plan->moves_a > plan->moves_b)
			return (plan->moves_a);
		return (plan->moves_b);
	}
	return (plan->moves_a + plan->moves_b);
}

static void	build_node_plan(t_program *prog, t_node *current_a,
		int pos_a, t_move_plan *node_plan)
{
	int	pos_b;

	node_plan->target_a = current_a;
	node_plan->moves_a = cost_calculator(pos_a, prog->a.size);
	node_plan->direction_a = get_direction(pos_a, prog->a.size);
	pos_b = find_target_b(&prog->b, current_a->value);
	node_plan->moves_b = cost_calculator(pos_b, prog->b.size);
	node_plan->direction_b = get_direction(pos_b, prog->b.size);
	node_plan->total_cost = get_move_cost(node_plan);
}

void	calculate_insertion_plan(t_program *prog, t_move_plan *best_plan)
{
	t_node		*current_a;
	int			pos_a;
	t_move_plan	current_node_plan;

	best_plan->total_cost = 2147483647;
	current_a = prog->a.head;
	pos_a = 0;
	while (current_a)
	{
		build_node_plan(prog, current_a, pos_a, &current_node_plan);
		if (current_node_plan.total_cost < best_plan->total_cost)
			*best_plan = current_node_plan;
		pos_a++;
		current_a = current_a->next;
	}
}
