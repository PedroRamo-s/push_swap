/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmedium_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:35:34 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/07/02 03:41:19 by aantela-         ###   ########.fr       */
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

static t_node	*max_selector_b(t_list *stack)
{
	t_node	*tmp;
	t_node	*best_node;
	int		i;

	tmp = stack->head;
	best_node = tmp;
	i = 0;
	while (i < stack->size)
	{
		if (tmp->index > best_node->index)
			best_node = tmp;
		tmp = tmp->next;
		i++;
	}
	return (best_node);
}

static int	get_position_b(t_list *stack, t_node *target)
{
	t_node	*tmp;
	int		pos;

	tmp = stack->head;
	pos = 0;
	while (tmp != target)
	{
		pos++;
		tmp = tmp->next;
	}
	return (pos);
}

static void	rotate_to_top_b(t_program *prog, t_node *target)
{
	int	distance;
	int	position;

	position = get_position_b(&prog->b, target);
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

/*
** Após cada pb, se o novo topo de B tiver índice MAIOR que o segundo,
** faz sb para manter B ordenado decrescente do topo.
** Isso reduz as rotações no drain porque o máximo fica mais perto do topo.
*/
static void	push_and_sort_b(t_program *prog)
{
	pb(prog);
	if (prog->b.size >= 2
		&& prog->b.head->index < prog->b.head->next->index)
		sb(prog);
}

void	push_chunks_b(t_program *prog)
{
	int		chunk_size;
	int		chunk_min;
	int		chunk_max;
	int		size;
	t_node	*selected_node;

	size = prog->a.size;
	chunk_size = size / 7;
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

void	sort_medium(t_program *prog)
{
	t_node	*best;
	if (prog->a.size < 4)
	{
		sort_three(prog);
		return ;
	}
	indexer(&prog->a);
	push_chunks_b(prog);
	while (prog->b.head)
	{
		best = max_selector_b(&prog->b);
		rotate_to_top_b(prog, best);
		pa(prog);
	}
}
