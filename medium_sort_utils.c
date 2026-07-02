/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_medium.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:36:26 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/17 14:36:27 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_assigner(t_stack *stack, int *values)
{
	int		i;
	int		j;
	int		rank;
	int		size;
	t_node	*tmp;

	i = 0;
	size = stack->size;
	tmp = stack->top;
	while (i < size)
	{
		j = 0;
		rank = 0;
		while (j < size)
		{
			if (values[i] > values[j])
				rank++;
			j++;
		}
		tmp->index = rank;
		tmp = tmp->next;
		i++;
	}
}

void	indexer(t_stack *stack)
{
	int	*values;

	values = array_filler(stack);
	if (!values)
		return ;
	index_assigner(stack, values);
	free(values);
}

int	chunk_count(int size)
{
	int	sq;

	sq = 1;
	while ((sq <= size))
	{
		if (sq * sq >= size)
			return (sq);
		sq++;
	}
	return (0);
}

int	cost_calculator(int position, int stack_size)
{
	if (position <= (stack_size / 2))
		return (position);
	return (stack_size - position);
}

void	rotate_to_top_pos(t_stack *a, t_stack *b, int position, t_bench *bench)
{
	int	distance;

	if (position <= a->size / 2)
		distance = position;
	else
		distance = position - a->size;
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
