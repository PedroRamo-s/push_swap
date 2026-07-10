/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:35:34 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/07/10 03:15:45 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	push_and_sort_b(t_program *prog)
{
	pb(prog);
	if (prog->b.size >= 2
		&& prog->b.head->index < prog->b.head->next->index)
		sb(prog);
}

void	medium_sort(t_program *prog)
{
	t_node	*best;

	if (prog->a.size < 6)
	{
		sort_five(prog);
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
