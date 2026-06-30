/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 14:50:12 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/17 05:12:48 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*static int is_three_largest(t_stack *a, int val)
{
    t_node  *curr;
    int     count;

    curr = a->top;
    count = 0;
    while (curr)
    {
        if (curr->value > val)
            count++;
        curr = curr->next;
    }
    if (count < 3)
        return (1);
    return (0);
}*/

void calculate_insertion_plan(t_stack *a, t_stack *b, t_move_plan *best_plan)
{
	t_node *current_a;
	int pos_a;

	best_plan->total_cost = 2147483647;
	current_a = a->top;
	pos_a = 0;

	while(current_a)
	{
		/*if (is_three_largest(a, current_a->value))
        {
            pos_a++;
            current_a = current_a->next;
            continue;
        }*/
		t_move_plan current_node_plan;
		int pos_b;

		current_node_plan.target_a = current_a;
		current_node_plan.moves_a = cost_calculator(pos_a, a->size);
		current_node_plan.direction_a = (pos_a <= a->size / 2) ? 0 : 1; 
		
		pos_b = find_target_b(b, current_a->value);
		current_node_plan.moves_b = cost_calculator(pos_b, b->size);
		current_node_plan.direction_b = (pos_b <= b->size / 2) ? 0 :1; 
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

/*static void	sort_three(t_stack *a, t_stack *b, t_bench *bench)
{
	int	top;
	int	mid;
	int	bot;

	if (a->size < 2)
		return ;
	if (a->size == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a, b, bench);
		return ;
	}
	top = a->top->value;
	mid = a->top->next->value;
	bot = a->top->next->next->value;
	if (top > mid && top > bot)
		ra(a, b, bench);
	else if (bot < top && bot < mid)
		rra(a, b, bench);
	if (a->top->value > a->top->next->value)
		sa(a, b, bench);
}*/

void plan_executor(t_stack *a, t_stack *b, t_move_plan *plan, t_bench *bench)
{
	if(plan->direction_a == 0 && plan->direction_b == 0)
	{
		while(plan->moves_a > 0 && plan->moves_b > 0)
		{
			rr(a, b, bench);
			plan->moves_a--;
			plan->moves_b--;
		}
	}
	if(plan->direction_a == 1 && plan->direction_b == 1)
	{
		while(plan->moves_a > 0 && plan->moves_b > 0)
		{
			rrr(a, b, bench);
			plan->moves_a--;
			plan->moves_b--;
		}
	}
	while(plan->moves_a > 0)
	{
		if(plan->direction_a == 0)
			ra(a, b, bench);
		else
			rra(a, b, bench);
		plan->moves_a--;
	}
	while(plan->moves_b > 0)
	{
		if(plan->direction_b == 0)
			rb(b, a, bench);
		else
			rrb(b, a, bench);
		plan->moves_b--;
	}
}

void	sort_simple(t_stack *a, t_stack *b, t_bench *bench)
{
	t_move_plan plan;
	int max_pos_b;
	int moves_b;
	int dir_b;

	/*if(a->size == 3)
	{
		sort_three(a, b, bench);
		return;
	}*/
	pb(a, b, bench);
	pb(a, b, bench);
	if(b->top->value < b->top->next->value)
		sb(b, a, bench);
	while(a->size > 0)
	{
		calculate_insertion_plan(a, b, &plan);
		plan_executor(a, b, &plan, bench);
		pb(a, b, bench);
	}

	//sort_three(a, b, bench);
	max_pos_b = find_max_pos(b);
	moves_b = cost_calculator(max_pos_b, b->size);
	dir_b = (max_pos_b <= b->size / 2) ? 0 : 1;

	while(moves_b > 0)
	{
		if(dir_b == 0)
			rb(b, a, bench);
		else
			rrb(b, a, bench);
		moves_b--;
	}

	while(b->top)
		pa(a, b, bench);
}
