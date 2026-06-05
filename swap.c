/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:15:36 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/03 16:15:37 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_node **stack_a)
{
	t_node	*first;
	t_node	*second;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	first = *stack_a;
	second = first->next;
	// 1. Handling 'first' links
	first->previous = second;   // first's previous link now points to second
	first->next = second->next; // first's next link now points towards hypothetical 'third'
	// 2. Handling the hypothetical 'third' link
	if (first->next != NULL)
		first->next = second->next;
	// 3. Handling the 'second' links
	second->previous = NULL; // second's previous is NULL, because it is the first node now
	second->next = first;    // second's next is first, since first is now the second link
	// 4. Update the main stack head pointer
	*stack_a = second;
}
