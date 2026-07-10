/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 16:12:25 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/10 03:15:49 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_dir_simple(int pos, int size)
{
	if (pos <= size / 2)
		return (0);
	return (1);
}

static void	insert_all_to_b(t_program *prog)
{
	t_move_plan	plan;

	while (prog->a.size > 0)
	{
		calculate_insertion_plan(prog, &plan);
		plan_executor(prog, &plan);
		pb(prog);
	}
}

static void	rotate_b_to_top(t_program *prog)
{
	int	max_pos_b;
	int	moves_b;
	int	dir_b;

	max_pos_b = find_max_pos(&prog->b);
	moves_b = cost_calculator(max_pos_b, prog->b.size);
	dir_b = get_dir_simple(max_pos_b, prog->b.size);
	while (moves_b > 0)
	{
		if (dir_b == 0)
			rb(prog);
		else
			rrb(prog);
		moves_b--;
	}
}

void	simple_sort(t_program *prog)
{
	if (prog->a.size < 6)
	{
		sort_five(prog);
		return ;
	}	
	pb(prog);
	pb(prog);
	if (prog->b.head->value < prog->b.head->next->value)
		sb(prog);
	insert_all_to_b(prog);
	rotate_b_to_top(prog);
	while (prog->b.head)
		pa(prog);
}
