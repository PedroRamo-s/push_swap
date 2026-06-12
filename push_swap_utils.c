/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:08:38 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/12 04:56:58 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*node_builder(int value)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->previous = NULL;
    node->value = value;
	return (node);
}
void	add_bottom(t_stack *stack, int value)
{
	t_node	*new_node;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node -> value = value;
	new_node -> next = NULL;
	if (stack -> size == 0)
	{
		new_node -> previous = NULL;
		stack -> top = new_node;
		stack -> bottom = new_node;
	}
	else
	{
		new_node -> previous = stack -> bottom;
		stack -> bottom -> next = new_node;
		stack -> bottom = new_node;
	}
	stack -> size++;
}

void	init_stack_a(t_stack *stack_a, int argc, char **argv, int start_index)
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
}
