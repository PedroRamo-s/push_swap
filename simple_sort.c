/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:38:35 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/09 16:38:37 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_to_top(t_node **stack_a, int smallest_index, int size)
{
	int	distance;

	if (smallest_index <= size / 2)
		distance = +smallest_index;
	else
		distance = smallest_index - size;
	while (distance > 0)
	{
		ra(stack_a);
		distance--;
	}
	while (distance < 0)
	{
		rra(stack_a);
		distance++;
	}
}

int	stack_size(t_node **stack)
{
	int		i;
	t_node	*current;

	i = 0;
	current = *stack;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	sort_three(t_node **stack)
{
	int	mid;
	int	bot;
	int	i;

	i = get_min_index(stack);
	if (i == 1)
		ra(stack);
	else if (i == 2)
		rra(stack);
	mid = (*stack)->next->value;
	bot = (*stack)->next->next->value;
	if (mid > bot)
	{
		rra(stack);
		sa(stack);
	}
}

void	simple_sort(t_node **stack_a, t_node **stack_b)
{
	int	size;
	int	smallest_index;

	size = stack_size(stack_a);
	while (size > 3)
	{
		smallest_index = get_min_index(stack_a);
		rotate_to_top(stack_a, smallest_index, size);
		pb(stack_a, stack_b);
		size--;
	}
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
}
