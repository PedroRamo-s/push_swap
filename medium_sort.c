/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:35:34 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/13 15:35:35 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_node_position(t_stack *stack, t_node *target_node)
{
	t_node	*current;
	int		position;

	current = stack->top;
	position = 0;
	
	while (current)
	{
		if (current == target_node)
			return (position);
		current = current->next;
		position++;
	}
	return (0);
}

t_node	*best_selector_a(t_stack *stack, int chunk_max, int chunk_min)
{
	t_node	*tmp;
	int		best_cost;
	t_node	*best_node;
	int		current_position;
	int		current_cost;

	tmp = stack->top;
	current_position = 0;
	best_node = NULL;
	best_cost = stack->size;
	while (tmp)
	{
		if (tmp->index >= chunk_min && tmp->index <= chunk_max)
		{
			if (tmp->index >= chunk_min && tmp->index <= chunk_max)
				printf("MATCH: %d\n", tmp->index);
			current_cost = cost_calculator(current_position, stack->size);
			if (current_cost < best_cost)
			{
				best_node = tmp;
				best_cost = current_cost;
			}
		}
		tmp = tmp->next;
		current_position++;
	}
	return (best_node);
}

t_node	*best_selector_b(t_stack *stack)
{
	t_node	*tmp;
	t_node	*best_node;

	tmp = stack->top;
	best_node = tmp;
	while (tmp)
	{
		if (tmp->index > best_node->index)
			best_node = tmp;
		tmp = tmp->next;
	}
	return (best_node);
}

void calculate_return_plan(t_stack *a, t_stack *b, t_move_plan *plan)
{
    t_node  *current_b;
    int     pos_b;
    int     pos_a; 

    plan->total_cost = 2147483647;
    current_b = b->top;
    pos_b = 0;

    while (current_b)
    {
        t_move_plan current_node_plan;

        current_node_plan.target_b = current_b;
        current_node_plan.moves_b = cost_calculator(pos_b, b->size);
        current_node_plan.direction_b = (pos_b <= b->size / 2) ? 0 : 1; 
        
        pos_a = find_target_a(a, current_b->index);
        current_node_plan.moves_a = cost_calculator(pos_a, a->size);
        current_node_plan.direction_a = (pos_a <= a->size / 2) ? 0 : 1; 
        
        if (current_node_plan.direction_a == current_node_plan.direction_b)
        {
            current_node_plan.total_cost = (current_node_plan.moves_a > current_node_plan.moves_b) ?
                                            current_node_plan.moves_a : current_node_plan.moves_b;
        }
        else
            current_node_plan.total_cost = current_node_plan.moves_a + current_node_plan.moves_b;
            
        if (current_node_plan.total_cost < plan->total_cost)
            *plan = current_node_plan;
            
        pos_b++;
        current_b = current_b->next;
    }
}

void	push_chunks_b(t_stack *stack_a, t_stack *stack_b, t_bench *bench)
{
	int		chunk_midpoint;
	int		pending_rb;
	int		chunk_size;
	int		chunk_num;
	int		chunk_min;
	int		chunk_max;
	double	size;
	t_node	*selected_node;
	int		a_direction;

	pending_rb = 0;
	size = stack_a->size;
	chunk_num = chunk_count(size);
	chunk_size = size / chunk_num;
	chunk_max = chunk_size - 1;
	chunk_min = 0;
	chunk_midpoint = chunk_min + (chunk_size / 2);
	while (chunk_min < size)
	{
		while (1)
		{
			selected_node = best_selector_a(stack_a, chunk_max, chunk_min);
			if (selected_node == NULL)
				break ;
			a_direction = (get_node_position(stack_a,
						selected_node) <= stack_a->size / 2) ? 0 : 1;
			if (pending_rb && a_direction == 0)
			{
				rr(stack_a, stack_b, bench);
				pending_rb = 0;
			}
			else if (pending_rb)
			{
				rb(stack_b, stack_a, bench);
				pending_rb = 0;
			}
			rotate_to_top(stack_a, stack_b, selected_node, bench);
			pb(stack_a, stack_b, bench);
			if (stack_b->top->index < chunk_midpoint)
				pending_rb = 1;
		}
		if (pending_rb)
		{
			rb(stack_b, stack_a, bench);
			pending_rb = 0;
		}
		chunk_min += chunk_size;
		chunk_max += chunk_size;
		chunk_midpoint += chunk_size;
	}
}

void	sort_medium(t_stack *stack_a, t_stack *stack_b, t_bench *bench)
{
	t_move_plan plan;
	int min_node;

	indexer(stack_a);
	push_chunks_b(stack_a, stack_b, bench);
	pa(stack_a, stack_b, bench);
	while (stack_b->top)
	{
		calculate_return_plan(stack_a, stack_b, &plan);
		plan_executor(stack_a, stack_b, &plan, bench);
		pa(stack_a, stack_b, bench);
	}
	min_node = find_min_pos(stack_a);
	rotate_to_top_pos(stack_a, stack_b, min_node, bench);
}
