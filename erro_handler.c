/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:08:31 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/13 07:08:58 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack *stack)
{
	t_node *current;
	t_node *next_node;

	if (!stack || !stack -> top)
		return ;
	current = stack -> top;
	while (current != NULL)
	{
		next_node = current -> next;
		free(current);
		current = next_node;
	}
	stack -> top = NULL;
	stack -> bottom = NULL;
	stack -> size = 0;
}

void	handle_error_and_exit(t_stack *stack)
{
	free_stack(stack);
	write(2, "Error\n", 6);
	exit(1);
}
