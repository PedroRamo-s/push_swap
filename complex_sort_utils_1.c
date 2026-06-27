/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:49:25 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/27 05:55:18 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_pos(t_list *s, t_node *target)
{
	t_node *tmp;
	int		pos;

	tmp = s->head;
	pos = 0;

	while (tmp != target)
	{
		pos++;
		tmp = tmp->next;
	}
	return (pos);
}

int	signed_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (pos - size);
}

int	compute_total(int ca, int cb)
{
	int	abs_a;
	int	abs_b;

	if (ca < 0)
		abs_a = -ca;
	else
		abs_a = ca;
	if (cb < 0)
		abs_b = -cb;
	else
		abs_b = cb;
	if ((ca >= 0 && cb >= 0) || (ca < 0 && cb < 0))
	{
		if (abs_a > abs_b)
			return (abs_a);
		return (abs_b);
	}
	return (abs_a + abs_b);
}

t_node	*stack_max(t_list *s)
{
	t_node	*tmp;
	t_node	*max;
	int		i;

	tmp = s->head;
	max = tmp;
	i = 0;
	while (i < s->size)
	{
		if (tmp->value > max->value)
			max = tmp;
		tmp = tmp->next;
		i++;
	}
	return (max);
}

t_node	*stack_min(t_list *s)
{
	t_node	*tmp;
	t_node	*min;
	int		i;

	tmp = s->head;
	min = tmp;
	i = 0;
	while (i < s->size)
	{
		if (tmp->value < min->value)
			min = tmp;
		tmp = tmp->next;
		i++;
	}
	return (min);
}
