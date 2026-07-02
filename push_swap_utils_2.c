/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_medium.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:36:26 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/17 14:36:27 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int find_max_pos(t_stack *b)
{
    t_node  *curr;
    int     max_val;
    int     max_pos;
    int     curr_pos;

    curr = b->top;
    max_val = curr->value;
    max_pos = 0;
    curr_pos = 0;
    while (curr)
    {
        if (curr->value > max_val)
        {
            max_val = curr->value;
            max_pos = curr_pos;
        }
        curr_pos++;
        curr = curr->next;
    }
    return (max_pos);
}

int find_target_b(t_stack *b, int value_a)
{
    t_node  *curr;
    int     pos;

    curr = b->top;
    pos = 1;
    while (curr->next)
    {
        if (curr->value > value_a && curr->next->value < value_a)
            return (pos);
        pos++;
        curr = curr->next;
    }
    if (curr->value > value_a && b->top->value < value_a)
        return (0); 
    return (find_max_pos(b));
}

int find_min_pos(t_stack *a)
{
    t_node  *curr;
    int     min_val;
    int     min_pos;
    int     curr_pos;

    curr = a->top;
    min_val = curr->value;
    min_pos = 0;
    curr_pos = 0;
    while (curr)
    {
        if (curr->value < min_val)
        {
            min_val = curr->value;
            min_pos = curr_pos;
        }
        curr = curr->next;
        curr_pos++;
    }
    return (min_pos);
}

int find_target_a(t_stack *a, int val_b)
{
    t_node  *curr;
    long    closest_larger;
    int     target_pos;
    int     curr_pos;

    curr = a->top;
    closest_larger = 2147483648;
    target_pos = -1;
    curr_pos = 0;
    while (curr)
    {
        if (curr->index > val_b && curr->index < closest_larger)
        {
            closest_larger = curr->index;
            target_pos = curr_pos;
        }
        curr = curr->next;
        curr_pos++;
    }
    if (target_pos == -1)
        return (find_min_pos(a));

    return (target_pos);
}

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