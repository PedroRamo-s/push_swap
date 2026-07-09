/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:15:46 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/09 15:55:18 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	cost_calculator(int position, int stack_size)
{
	if (position <= (stack_size / 2))
		return (position);
	return (stack_size - position);
}

t_node	*best_selector_a(t_list *stack, int chunk_max, int chunk_min)
{
	t_node	*tmp;
	t_node	*best_node;
	int		best_cost;
	int		current_position;
	int		current_cost;

	tmp = stack->head;
	current_position = 0;
	best_node = NULL;
	best_cost = stack->size + 1;
	while (current_position < stack->size)
	{
		if (tmp->index >= chunk_min && tmp->index <= chunk_max)
		{
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

void	push_chunks_b(t_program *prog)
{
	int		chunk_size;
	int		chunk_min;
	int		chunk_max;
	int		size;
	t_node	*selected_node;

	size = prog->a.size;
	chunk_size = 1.8 * ft_sqrt(size);
	if (chunk_size < 1)
		chunk_size = 1;
	chunk_max = chunk_size - 1;
	chunk_min = 0;
	while (chunk_min < size)
	{
		while (1)
		{
			selected_node = best_selector_a(&prog->a, chunk_max, chunk_min);
			if (selected_node == NULL)
				break ;
			rotate_to_top(&prog->a, selected_node, prog);
			push_and_sort_b(prog);
		}
		chunk_min += chunk_size;
		chunk_max += chunk_size;
	}
}
