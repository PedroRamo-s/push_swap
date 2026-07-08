/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:22:13 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/06 15:32:57 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_values(t_program *prog, int a, int b, int c)
{
	if (a < b && b < c)
		return ;
	else if (a < c && c < b)
	{
		sa(prog);
		ra(prog);
	}
	else if (b < a && a < c)
		sa(prog);
	else if (b < c && c < a)
		ra(prog);
	else if (c < a && a < b)
		rra(prog);
	else if (c < b && b < a)
	{
		sa(prog);
		rra(prog);
	}
}

void	sort_three(t_program *prog)
{
	int	a;
	int	b;
	int	c;

	if (prog->a.size < 2)
		return ;
	if (prog->a.size == 2)
	{
		sa(prog);
		return ;
	}
	a = prog->a.head->value;
	b = prog->a.head->next->value;
	c = prog->a.tail->value;
	sort_three_values(prog, a, b, c);
}

static void	rotate_both(t_program *prog, t_move_plan *plan)
{
	if (plan->direction_a == 0 && plan->direction_b == 0)
	{
		while (plan->moves_a > 0 && plan->moves_b > 0)
		{
			rr(prog);
			plan->moves_a--;
			plan->moves_b--;
		}
	}
	if (plan->direction_a == 1 && plan->direction_b == 1)
	{
		while (plan->moves_a > 0 && plan->moves_b > 0)
		{
			rrr(prog);
			plan->moves_a--;
			plan->moves_b--;
		}
	}
}

static void	rotate_remaining(t_program *prog, t_move_plan *plan)
{
	while (plan->moves_a > 0)
	{
		if (plan->direction_a == 0)
			ra(prog);
		else
			rra(prog);
		plan->moves_a--;
	}
	while (plan->moves_b > 0)
	{
		if (plan->direction_b == 0)
			rb(prog);
		else
			rrb(prog);
		plan->moves_b--;
	}
}

void	plan_executor(t_program *prog, t_move_plan *plan)
{
	rotate_both(prog, plan);
	rotate_remaining(prog, plan);
}
