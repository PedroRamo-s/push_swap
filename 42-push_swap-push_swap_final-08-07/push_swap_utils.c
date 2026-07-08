/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:08:38 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/07/04 04:42:15 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	create_and_add_bottom(t_list *stack, int value)
{
	t_node	*new_node;

	if (!stack)
		return ;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node -> value = value;
	new_node -> next = NULL;
	new_node -> index = 0;
	if (stack -> size == 0 || !stack -> head)
	{
		new_node -> previous = NULL;
		stack -> head = new_node;
		stack -> tail = new_node;
		stack -> size = 1;
	}
	else
	{
		new_node -> previous = stack -> tail;
		stack -> tail -> next = new_node;
		stack -> tail = new_node;
		stack -> size++;
	}
}

void	rotate_to_top(t_list *stack, t_node *target, t_program *prog)
{
	int		distance;
	int		position;
	t_node	*tmp;

	tmp = stack -> head;
	position = 0;
	while (tmp != target)
	{
		position++;
		tmp = tmp->next;
	}
	if (position <= stack -> size / 2)
		distance = position;
	else
		distance = position - stack -> size;
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

int	*array_filler(t_list *stack)
{
	int		*values;
	int		size;
	int		i;
	t_node	*tmp;

	i = 0;
	size = stack->size;
	tmp = stack->head;
	values = malloc(size * sizeof(int));
	if (!values)
		return (NULL);
	while (i < size)
	{
		values[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	return (values);
}

int	find_max_pos(t_list *b)
{
	t_node	*curr;
	int		max_val;
	int		max_pos;
	int		curr_pos;

	curr = b->head;
	max_val = curr->value;
	max_pos = 0;
	curr_pos = 0;
	while (curr)
	{
		if (curr->value > max_val)
		{
			max_val = curr->value;
			max_pos = curr_pos;
		}
		curr_pos++;
		curr = curr->next;
	}
	return (max_pos);
}

int	find_target_b(t_list *b, int value_a)
{
	t_node	*curr;
	int		pos;

	curr = b->head;
	pos = 1;
	while (curr->next)
	{
		if (curr->value > value_a && curr->next->value < value_a)
			return (pos);
		pos++;
		curr = curr->next;
	}
	if (curr->value > value_a && b->head->value < value_a)
		return (0);
	return (find_max_pos(b));
}
