/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 16:12:25 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/01 03:22:45 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void calculate_insertion_plan(t_program *prog, t_move_plan *best_plan)
{
	t_node *current_a;
	int pos_a;

	best_plan->total_cost = 2147483647;
	current_a = prog-> a.head;
	pos_a = 0;

	while(current_a)
	{
		t_move_plan current_node_plan;
		int pos_b;

		current_node_plan.target_a = current_a;
		current_node_plan.moves_a = cost_calculator(pos_a, prog->a.size);
		current_node_plan.direction_a = (pos_a <= prog->a.size / 2) ? 0 : 1; 
		
		pos_b = find_target_b(&prog->b, current_a->value);
		current_node_plan.moves_b = cost_calculator(pos_b, prog -> b.size);
		current_node_plan.direction_b = (pos_b <= prog -> b.size / 2) ? 0 :1; 
		if(current_node_plan.direction_a == current_node_plan.direction_b)
		{
			current_node_plan.total_cost = (current_node_plan.moves_a > current_node_plan.moves_b) ?
											current_node_plan.moves_a : current_node_plan.moves_b;
		}
		else
			current_node_plan.total_cost = current_node_plan.moves_a + current_node_plan.moves_b;
		if(current_node_plan.total_cost < best_plan->total_cost)
			*best_plan = current_node_plan;
		pos_a++;
		current_a = current_a->next;
	}
}

void plan_executor(t_program *prog, t_move_plan *plan)
{
	if(plan->direction_a == 0 && plan->direction_b == 0)
	{
		while(plan->moves_a > 0 && plan->moves_b > 0)
		{
			rr(prog);
			plan->moves_a--;
			plan->moves_b--;
		}
	}
	if(plan->direction_a == 1 && plan->direction_b == 1)
	{
		while(plan->moves_a > 0 && plan->moves_b > 0)
		{
			rrr(prog);
			plan->moves_a--;
			plan->moves_b--;
		}
	}
	while(plan->moves_a > 0)
	{
		if(plan->direction_a == 0)
			ra(prog);
		else
			rra(prog);
		plan->moves_a--;
	}
	while(plan->moves_b > 0)
	{
		if(plan->direction_b == 0)
			rb(prog);
		else
			rrb(prog);
		plan->moves_b--;
	}
}

void    sort_three(t_program *prog)
{
    int head;
    int mid;
    int bot;

    if (prog->a.size < 2)
        return ;
    if (prog->a.size == 2)
    {
        if (prog->a.head->value > prog->a.head->next->value)
            sa(prog);
        return ;
    }
    head = prog->a.head->value;
    mid = prog->a.head->next->value;
    bot = prog->a.head->next->next->value;
    if (head > mid && head > bot)
        ra(prog);
    else if (bot < head && bot < mid)
        rra(prog);
    else if (mid > head && mid > bot)
    {
        sa(prog);
        ra(prog);
    }
    if (prog->a.head->value > prog->a.head->next->value)
        sa(prog);
}

void	sort_simple(t_program *prog)
{
	t_move_plan plan;
	int max_pos_b;
	int moves_b;
	int dir_b;
	if (prog->a.size < 4)
	{
		sort_three(prog);
		return ;
	}
	pb(prog);
	pb(prog);
	if(prog->b.head->value <prog->b.head->next->value)
		sb(prog);
	while(prog->a.size > 0)
	{
		calculate_insertion_plan(prog, &plan);
		plan_executor(prog, &plan);
		pb(prog);
	}
	max_pos_b = find_max_pos(&prog->b);
	moves_b = cost_calculator(max_pos_b, prog->b.size);
	dir_b = (max_pos_b <= prog->b.size / 2) ? 0 : 1;

	while(moves_b > 0)
	{
		if(dir_b == 0)
			rb(prog);
		else
			rrb(prog);
		moves_b--;
	}

	while(prog->b.head)
		pa(prog);
}
