/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_teste.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:35:34 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/25 15:55:40 by aantela-         ###   ########.fr       */
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
	int		best_cost;
	t_node	*best_node;
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

t_node	*best_selector_b(t_list *stack)
{
	t_node	*tmp;
	t_node	*best_node;
	int		current_position;

	tmp = stack->head;
	best_node = tmp;
	current_position = 0;
	while (current_position < stack->size)
	{
		if (tmp->index > best_node->index)
			best_node = tmp;
		tmp = tmp->next;
		current_position++;
	}
	return (best_node);
}

static void	rotate_to_top_b(t_program *prog, t_node *target)
{
	int		distance;
	int		position;
	t_node	*tmp;

	tmp = prog->b.head;
	position = 0;
	while (tmp != target)
	{
		position++;
		tmp = tmp->next;
	}
	if (position <= prog->b.size / 2)
		distance = position;
	else
		distance = position - prog->b.size;
	while (distance > 0)
	{
		rb(prog);
		distance--;
	}
	while (distance < 0)
	{
		rrb(prog);
		distance++;
	}
}

void	push_chunks_b(t_program *prog)
{
	int		chunk_size;
	int		chunk_min;
	int		chunk_max;
	int		size;
	t_node	*selected_node;

	size = prog->a.size;
	chunk_size = size / 5;
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
			pb(prog);
		}
		chunk_min += chunk_size;
		chunk_max += chunk_size;
	}
}

void	sort_medium(t_program *prog)
{
	t_node	*selected_node;

	indexer(&prog->a);
	push_chunks_b(prog);
	while (prog->b.head)
	{
		selected_node = best_selector_b(&prog->b);
		rotate_to_top_b(prog, selected_node);
		pa(prog);
	}
}
