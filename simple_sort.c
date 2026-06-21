/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 14:50:12 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/21 20:13:29 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_index(t_stack *a)
{
	t_node	*current;
	int		min;
	int		index;
	int		min_index;

	current = a->top;
	min = current->value;
	index = 0;
	min_index = 0;
	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			min_index = index;
		}
		index++;
		current = current->next;
	}
	return (min_index);
}

static void	rotate_to_top(t_stack *a, t_stack *b, int min_index, t_bench *bench)
{
	int	distance;

	if (min_index <= a->size / 2)
		distance = min_index;
	else
		distance = min_index - a->size;
	while (distance > 0)
	{
		ra(a, b, bench);
		distance--;
	}
	while (distance < 0)
	{
		rra(a, b, bench);
		distance++;
	}
}

void	sort_three(t_stack *a, t_stack *b, t_bench *bench)
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
	else if (mid > top && mid > bot)
	{
		sa (a, b, bench);
		ra(a , b, bench);
	}
	if (a->top->value > a->top->next->value)
		sa(a, b, bench);
}

void	sort_simple(t_stack *a, t_stack *b, t_bench *bench)
{
	while (a->size > 3)
	{
		rotate_to_top(a, b, get_min_index(a), bench);
		if (is_sorted(a))
			break ;
		pb(a, b, bench);
	}
	sort_three(a, b, bench);
	while (b->top)
		pa(a, b, bench);
}
