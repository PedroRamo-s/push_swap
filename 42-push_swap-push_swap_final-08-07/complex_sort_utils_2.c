/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:59:26 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/27 06:00:31 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Encontra a posição em A onde val deve ser inserido.
** pa coloca o elemento no HEAD de A. Para manter A ordenada crescente,
** precisamos que o SUCCESSOR (primeiro elemento > val) esteja no topo.
** Assim pa insere val antes do successor = posição correta.
** Se val é maior que tudo, o successor é o mínimo (wrap-around).
*/
int	find_target_a(t_list *a, int val)
{
	t_node	*tmp;
	t_node	*best;
	int		i;

	tmp = a->head;
	best = NULL;
	i = 0;
	while (i < a->size)
	{
		if (tmp->value > val)
		{
			if (best == NULL || tmp->value < best->value)
				best = tmp;
		}
		tmp = tmp->next;
		i++;
	}
	if (best == NULL)
		return (get_pos(a, stack_min(a)));
	return (get_pos(a, best));
}

/*
** Custo de mover o nó node de B para a posição correta em A.
*/
int	node_cost(t_list *a, t_list *b, t_node *node)
{
	int	pos_b;
	int	pos_a;
	int	cb;
	int	ca;

	pos_b = get_pos(b, node);
	pos_a = find_target_a(a, node->value);
	cb = signed_cost(pos_b, b->size);
	ca = signed_cost(pos_a, a->size);
	return (compute_total(ca, cb));
}

/*
** Encontra o nó de B com menor custo total para inserir em A.
*/
t_node	*find_cheapest(t_list *a, t_list *b)
{
	t_node	*tmp;
	t_node	*cheapest;
	int		best_cost;
	int		cost;
	int		i;

	tmp = b->head;
	cheapest = tmp;
	best_cost = node_cost(a, b, tmp);
	i = 1;
	tmp = tmp->next;
	while (i < b->size)
	{
		cost = node_cost(a, b, tmp);
		if (cost < best_cost)
		{
			best_cost = cost;
			cheapest = tmp;
		}
		tmp = tmp->next;
		i++;
	}
	return (cheapest);
}
