/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:08:31 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/04 04:43:19 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_list *stack)
{
	t_node	*current;
	t_node	*next_node;

	if (!stack || !stack -> head)
		return ;
	current = stack -> head;
	while (current != NULL)
	{
		next_node = current -> next;
		free(current);
		current = next_node;
	}
	stack -> head = NULL;
	stack -> tail = NULL;
	stack -> size = 0;
}

void	free_all_stack(t_program *prog)
{
	free_stack(&prog->a);
	free_stack(&prog->b);
}
