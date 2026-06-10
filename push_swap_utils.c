/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:08:38 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/10 05:01:05 by aantela-         ###   ########.fr       */
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
void	append_node(t_node **stack, t_node *new_node)
{
	t_node	*last;

	if (!stack || !new_node)
		return ;
	// Se a stack estiver vazia, o novo nó passa a ser o primeiro
	if (*stack == NULL)
	{
		*stack = new_node;
		return ;
	}
	// Caso contrário, navega até ao último nó atual
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	// Conecta o último nó ao novo nó e vice-versa
	last->next = new_node;
	new_node->previous = last;
}

int	init_stack_a(t_node **stack_a, int argc, char **argv)
{
	int		i;
	int		value;
	t_node	*new_node;

	i = 1; // Começa no 1 para saltar o nome do programa
	while (i < argc)
	{
		// 1. Verifica Sintaxe e Overflow ao mesmo tempo
		if (!is_numeric(argv[i]) || !ft_atoi_safe(argv[i], &value))
		{
			free_stack(stack_a); // Limpa o que já tinha sido alocado
			return (0); // Sinaliza erro para o main
		}
		// 2. Verifica se o número já existe na stack_a
		if (has_duplicate(*stack_a, value))
		{
			free_stack(stack_a);
			return (0);
		}
		// 3. Cria o novo nó usando o node_builder
		new_node = node_builder(value);
		if (!new_node)
		{
			free_stack(stack_a);
			return (0);
		}
		// 4. Adiciona o nó no fim da stack
		append_node(stack_a, new_node);
		i++;
	}
	return (1); // Stack criada e limpa
}
