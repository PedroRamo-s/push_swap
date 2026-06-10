/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:08:31 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/10 05:18:56 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit (1);
}

void	free_stack(t_node **stack)
{
	t_node *current;
	t_node *tmp;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current != NULL)
	{
		tmp = current -> next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}
