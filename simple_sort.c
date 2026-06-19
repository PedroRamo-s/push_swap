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

static t_node	*get_min_index(t_stack *a)
{
	t_node	*current;
	int		min;
	int		index;
	t_node	*min_node;

	current = a->top;
	min = current->value;
	index = 0;
	min_node = a->top;
	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			min_node = current;
		}
		index++;
		current = current->next;
	}
	return (min_node);
}

static void	sort_three(t_stack *a, t_stack *b, t_bench *bench)
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
}

void	sort_simple(t_stack *a, t_stack *b, t_bench *bench)
{
	while (a->size > 3)
	{
		rotate_to_top(a, b, get_min_index(a), bench);
		if (is_sorted(a))
			return ;
		pb(a, b, bench);
	}
	sort_three(a, b, bench);
	while (b->top)
		pa(a, b, bench);
}
