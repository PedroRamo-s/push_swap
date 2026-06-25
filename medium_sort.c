/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:35:34 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/25 15:51:46 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	cost_calculator(int position, int stack_size)
{
	if (position <= (stack_size / 2))
		return (position);
	printf("faz alguma coisa seila oi que \n");
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
	best_cost = stack->size;
	while (current_position < stack -> size)
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
	printf("retorna best mode a\n");
	return (best_node);
}

t_node	*best_selector_b(t_list *stack)
{
	t_node	*tmp;
	t_node	*best_node;
	int	current_position;

	tmp = stack->head;
	best_node = tmp;
	current_position = 0;
	while (current_position < stack -> size)
	{
		if (tmp->index > best_node->index)
			best_node = tmp;
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
	double	size;
	t_node	*selected_node;

	size = prog -> a.size;
	chunk_size = ft_sqrt(size);
	chunk_max = chunk_size - 1;
	chunk_min = 0;
	while (chunk_min < size)
	{
		while (1)
		{
			selected_node = best_selector_a(&prog->a, chunk_max, chunk_min);
			if (selected_node == NULL)
				break ;
			rotate_to_top(&prog-> a, selected_node, prog);
			pb(prog);
		}
		chunk_min += chunk_size;
		chunk_max += chunk_size;
	}
	printf("terminou o chunk\n");
}

void	sort_medium(t_program *prog)
{
	t_node	*selected_node;

	printf("iniciou medium\n");
	indexer(&prog -> a);
	printf("retorno indexer\n");
	push_chunks_b(prog);
	printf("retorno push_chunks\n");
	while (prog -> b.head)
	{
		selected_node = best_selector_b(&prog -> b);
		rotate_to_top (&prog ->b, selected_node, prog);
		pa(prog);
	}
}
