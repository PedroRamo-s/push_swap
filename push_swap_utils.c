/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:08:38 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/25 15:26:01 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*t_node	*node_builder(int value)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->previous = NULL;
    node->value = value;
	return (node);
}*/
void	create_and_add_bottom(t_list *stack, int value)
{
	if (!stack)
		return ;
	t_node	*new_node;
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

/*void	init_stack_a(t_stack *stack_a, int argc, char **argv, int start_index)
{
	int	value;
	stack_a -> top = NULL;
	stack_a -> bottom = NULL;
	stack_a -> size = 0;
	while (start_index < argc)
	{
		if (!is_numeric(argv[start_index]))
			handle_error_and_exit(stack_a);
		if (ft_atoi_safe(argv[start_index], &value) == 0)
			handle_error_and_exit(stack_a);
		if (has_duplicate(stack_a, value))
			handle_error_and_exit(stack_a);
		add_bottom(stack_a, value);
		start_index++;
	}
}*/

void	rotate_to_top(t_list *stack , t_node *target, t_program *prog)
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
