/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 04:16:52 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/03 04:17:10 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_insert_index(t_list stack, int val)
{
	t_node	*cur;
	int		i;
	int		idx;

	cur = stack.head;
	i = 0;
	idx = stack.size;
	while (i < stack.size)
	{
		if (cur->value > val)
		{
			idx = i;
			break ;
		}
		cur = cur->next;
		i++;
	}
	return (idx);
}

static void	rotate_index_to_top_a(t_program *prog, int idx, int size)
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

void	insert_back(t_program *prog)
{
	int	val;
	int	idx;

	val = prog->b.head->value;
	idx = find_insert_index(prog->a, val);
	rotate_index_to_top_a(prog, idx, prog->a.size);
	pa(prog);
}
