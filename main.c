/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 04:34:56 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/12 04:48:41 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*void	stack_printer(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("[%d], ", current->value);
		if ((current->previous) != NULL)
		{
			ft_printf("previous is: [%d], ", current->previous->value);
		}
		else
		{
			ft_printf("(Previous = NULL), ");
		}
		current = current->next;
	}
	ft_printf("-> NULL\n");
}
*/
void	debug_print_stack(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
	{
		printf("Stack Vazia!\n");
		return ;
	}
	current = stack->top;
	printf("Stack (Tamanho %d): ", stack->size);
	while (current)
	{
		printf("[%d] ", current->value);
		current = current->next;
	}
	printf("\n");
}
int	main(int argc, char **argv)
{
	t_config	config;
	t_stack		stack_a;
	t_stack		stack_b;
	int			start_index;

	if (argc < 2)
		return (0);
	start_index = parse_flags(argc, argv, &config);
	if (start_index == argc)
		return (0);
	stack_b.top = NULL;
	stack_b.bottom = NULL;
	stack_b.size = 0;
	init_stack_a(&stack_a, argc, argv, start_index);
	printf("Modo Bench: %d | Estratégia: %d\n", config.bench_mode, config.strategy);
	debug_print_stack(&stack_a);
	printf("Stack A populada com sucesso! Tamanho: %d\n", stack_a.size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
