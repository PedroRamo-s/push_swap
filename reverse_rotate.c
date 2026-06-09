/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:08:39 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/07 19:08:40 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_node **stack)
{
	t_node	*first;
	t_node	*last;
	t_node	*current;

	first = *stack;
	current = *stack;
	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	while (current->next != NULL)
	{
		current = current->next;
	}
	/*last = current;
	current->previous = NULL;
	current->next = first;
    current = *stack;
	first->previous = current;
	last->previous->next = NULL;*/
    last = current;
    current->previous = NULL;
    current->next = first;
    current = *stack;
}
