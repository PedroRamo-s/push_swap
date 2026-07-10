/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 04:17:23 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/09 16:07:04 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	index_of_min(t_list stack)
{
	t_node	*cur;
	int		min_val;
	int		min_idx;
	int		i;

	cur = stack.head;
	min_val = cur->value;
	min_idx = 0;
	i = 0;
	while (i < stack.size)
	{
		if (cur->value < min_val)
		{
			min_val = cur->value;
			min_idx = i;
		}
		cur = cur->next;
		i++;
	}
	return (min_idx);
}

static void	rotate_index_to_top(t_program *prog, int idx, int size)
{
	if (idx <= size / 2)
	{
		while (idx-- > 0)
			ra(prog);
	}
	else
	{
		while (idx++ < size)
			rra(prog);
	}
}

static void	push_smallest_to_b(t_program *prog)
{
	int	idx;

	idx = index_of_min(prog->a);
	rotate_index_to_top(prog, idx, prog->a.size);
	pb(prog);
}

void	sort_five(t_program *prog)
{
	if (prog->a.size < 4)
	{
		sort_three(prog);
		return ;
	}
	push_smallest_to_b(prog);
	push_smallest_to_b(prog);
	sort_three(prog);
	insert_back(prog);
	insert_back(prog);
}
