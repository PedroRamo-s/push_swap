/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 14:50:12 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/24 21:51:07 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_index(t_list *a)
{
	t_node	*current;
	int		min;
	int		index;
	int		min_index;

	current = a->head;
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

static void	otate_to_top(t_program *prog, int min_index)
{
	int	distance;

	if (min_index <= prog->a.size / 2)
		distance = min_index;
	else
		distance = min_index - prog->a.size;
	while (distance > 0)
	{
		ra(prog);
		distance--;
	}
	while (distance < 0)
	{
		rra(prog);
		distance++;
	}
}

void	sort_three(t_program *prog)
{
	int	head;
	int	mid;
	int	bot;

	if (prog->a.size < 2)
		return ;
	if (prog->a.size == 2)
	{
		if (prog->a.head->value > prog->a.head->next->value)
			sa(prog);
		return ;
	}
	head = prog->a.head->value;
	mid = prog->a.head->next->value;
	bot = prog->a.head->next->next->value;
	if (head > mid && head > bot)
		ra(prog);
	else if (bot < head && bot < mid)
		rra(prog);
	else if (mid > head && mid > bot)
	{
		sa(prog);
		ra(prog);
	}
	if (prog->a.head->value > prog->a.head->next->value)
		sa(prog);
}

void	sort_simple(t_program *prog)
{
	if (prog->a.size < 2 || is_sorted(&prog->a))
		return ;
	while (prog->a.size > 3)
	{
		otate_to_top(prog, get_min_index(&prog->a));
		if (is_sorted(&prog->a))
			break ;
		pb(prog);
	}
	sort_three(prog);
	while (prog->b.head)
		pa(prog);
}
