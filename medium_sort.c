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
#include <stdio.h>

int	cost_calculator(int position, int stack_size)
{
	if (position <= (stack_size / 2))
		return (position);
	return (stack_size - position);
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

void	push_chunks_b(t_stack *stack_a, t_stack *stack_b, t_bench *bench)
{
	int		chunk_size;
	int chunk_num;
	int		chunk_min;
	int		chunk_max;
	double	size;
	t_node	*selected_node;

	size = stack_a->size;
	chunk_num = ft_sqrt(size);
	chunk_size = size / chunk_num;
	chunk_max = chunk_size - 1;
	chunk_min = 0;
	while (chunk_min < size)
	{
		while (1)
		{
			selected_node = best_selector_a(stack_a, chunk_max, chunk_min);
			if (selected_node == NULL)
				break ;
			rotate_to_top(stack_a, stack_b, selected_node, bench);
			pb(stack_a, stack_b, bench);
		}
		chunk_min += chunk_size;
		chunk_max += chunk_size;
	}
}

void	sort_medium(t_stack *stack_a, t_stack *stack_b, t_bench *bench)
{
	t_node	*selected_node;

	indexer(stack_a);
	push_chunks_b(stack_a, stack_b, bench);
	while (stack_b->top)
	{
		selected_node = best_selector_b(stack_b);
		rotate_to_top(stack_b, stack_a, selected_node, bench);
		pa(stack_a, stack_b, bench);
	}
}
