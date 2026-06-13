/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 05:40:06 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/13 05:47:13 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    debug_print_stack(t_stack *stack)
{
	t_node  *current;
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

// Função auxiliar interna do main para processar matrizes vindas do split ou do argv
void	process_arguments(t_stack *stack_a, int count, char **args, int start, int is_split)
{
	int	value;

	while (start < count)
	{
		if (!is_numeric(args[start]))
		{
			if (is_split)
				free_array(args);
			handle_error_and_exit(stack_a);
		}
		if (ft_atoi_safe(args[start], &value) == 0)
		{
			if (is_split)
				free_array(args);
			handle_error_and_exit(stack_a);
		}
		if (has_duplicate(stack_a, value))
		{
			if (is_split)
				free_array(args);
			handle_error_and_exit(stack_a);
		}
		add_bottom(stack_a, value);
		start++;
	}
	if (is_split)
		free_array(args);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_stack		stack_a;
	t_stack		stack_b;
	int			start_index;
	char		**split_args;

	if (argc < 2)
		return (0);
	start_index = parse_flags(argc, argv, &config);
	if (start_index == argc)
		return (0);

	// Inicializa Stacks
	stack_a.top = NULL; stack_a.bottom = NULL; stack_a.size = 0;
	stack_b.top = NULL; stack_b.bottom = NULL; stack_b.size = 0;

	// CASO ESPECIAL: Sobrou apenas 1 argumento (ex: "1 2 3 4 5")
	if (start_index == argc - 1)
	{
		split_args = ft_split(argv[start_index]); // Divide por espaços
		if (!split_args || !split_args[0])
		{
			free_array(split_args);
			return (0); // String vazia "" fecha silenciosamente ou lida como erro
		}
		// Conta quantos elementos o split gerou
		int split_count = 0;
		while (split_args[split_count])
			split_count++;
		process_arguments(&stack_a, split_count, split_args, 0, 1);
	}
	else // CASO PADRÃO: Múltiplos argumentos separados (ex: 1 2 3 4 5)
	{
		process_arguments(&stack_a, argc, argv, start_index, 0);
	}

	// VERIFICAÇÃO DE OURO: Se a stack já veio totalmente ordenada de fábrica
	if (is_sorted(&stack_a))
	{
		free_stack(&stack_a);
		return (0); // Termina silenciosamente sem fazer nada, como manda o sujeito!
	}

	// --- A partir daqui, chamas o algoritmo do teu par ---
	// exemplo: start_sorting(&stack_a, &stack_b, &config);
	printf("Modo Bench: %d | Estratégia: %d\n", config.bench_mode, config.strategy);
	debug_print_stack(&stack_a);
	printf("Stack A populada com sucesso! Tamanho: %d\n", stack_a.size);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
