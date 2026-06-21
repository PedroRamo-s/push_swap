/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_complex1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:58:24 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/19 02:59:08 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Para um valor de A, encontra o indice em B onde deve ser inserido.
** B e mantido em ordem descendente circular.
** Queremos o no em B com o maior valor MENOR que val.
** Se nao existir (val e o novo minimo), o alvo e o maximo de B
** (val encaixa acima do max no "corte" circular).
*/
int	find_target_b(t_stack *b, int val)
{
	t_node	*cur;
	t_node	*best;

	if (!b || !b->top)
		return (0);
	cur = b->top;
	best = NULL;
	while (cur)
	{
		if (cur->value < val && (!best || cur->value > best->value))
			best = cur;
		cur = cur->next;
	}
	if (!best)
		best = stack_max(b);
	return (get_pos(b, best));
}

/*
** Para um valor de B, encontra o indice em A onde deve ser inserido.
** A e mantido em ordem ascendente circular.
** Queremos o no em A com o menor valor MAIOR que val.
** Se nao existir (val e o novo maximo), o alvo e o minimo de A.
*/
int	find_target_a(t_stack *a, int val)
{
	t_node	*cur;
	t_node	*best;

	cur = a->top;
	best = NULL;
	while (cur)
	{
		if (cur->value > val && (!best || cur->value < best->value))
			best = cur;
		cur = cur->next;
	}
	if (!best)
		best = stack_min(a);
	return (get_pos(a, best));
}

/*
** Calcula o custo total de empurrar um no de A para a posicao
** correcta em B (custos assinados com truque de rotacao simultanea).
*/
int	node_cost(t_stack *a, t_stack *b, t_node *node)
{
	int	pos_a;
	int	pos_b;
	int	ca;
	int	cb;

	pos_a = get_pos(a, node);
	pos_b = find_target_b(b, node->value);
	ca = signed_cost(pos_a, a->size);
	cb = signed_cost(pos_b, b->size);
	return (compute_total(ca, cb));
}

/*
** Itera todos os nos de A e devolve o que tem menor custo total.
*/
t_node	*find_cheapest(t_stack *a, t_stack *b)
{
	t_node	*cur;
	t_node	*best;
	int		best_cost;
	int		cur_cost;

	cur = a->top;
	best = cur;
	best_cost = node_cost(a, b, best);
	cur = cur->next;
	while (cur)
	{
		cur_cost = node_cost(a, b, cur);
		if (cur_cost < best_cost)
		{
			best = cur;
			best_cost = cur_cost;
		}
		cur = cur->next;
	}
	return (best);
}
