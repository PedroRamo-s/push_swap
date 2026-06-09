/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 01:06:03 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/06 01:06:05 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	rotate(t_node **stack)
{
	t_node *current;
	t_node *first;
	t_node *last;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	first = *stack;
    current = *stack;
	*stack = first->next;
	(*stack)->previous = NULL;
	while ((current->next) != NULL)
	{
		current = current->next;
	}
	last = current;
	current->next = first;
	first->previous = last;
	first->next = NULL;
}

void ra(t_node **stack_a)
{
    rotate(stack_a);
    ft_printf("ra\n");
}

void rb(t_node **stack_b)
{
    rotate(stack_b);
    ft_printf("rb\n");
}