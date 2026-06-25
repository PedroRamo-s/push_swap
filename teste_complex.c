/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_complex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:56:54 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/19 02:57:48 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Devolve o indice (0-based a partir do topo) de um no na stack.
*/
int	get_pos(t_stack *s, t_node *target)
{
	t_node	*cur;
	int		pos;

	cur = s->top;
	pos = 0;
	while (cur && cur != target)
	{
		pos++;
		cur = cur->next;
	}
	return (pos);
}

/*
** Custo assinado para rodar uma stack:
**   + pos  -> ra/rb (frente)
**   - dist -> rra/rrb (tras)
*/
int	signed_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (pos - size);
}

/*
** Custo total com o truque das rotacoes simultaneas:
** se ca e cb tiverem o mesmo sinal, rodamos as duas ao mesmo tempo
** (custa max em vez de soma).
*/
int	compute_total(int ca, int cb)
{
	int	abs_a;
	int	abs_b;

	abs_a = ca < 0 ? -ca : ca;
	abs_b = cb < 0 ? -cb : cb;
	if ((ca >= 0 && cb >= 0) || (ca <= 0 && cb <= 0))
	{
		if (abs_a > abs_b)
			return (abs_a);
		return (abs_b);
	}
	return (abs_a + abs_b);
}

/*
** Devolve o no com o maior valor na stack.
*/
t_node	*stack_max(t_stack *s)
{
	t_node	*cur;
	t_node	*max;

	cur = s->top;
	max = cur;
	while (cur)
	{
		if (cur->value > max->value)
			max = cur;
		cur = cur->next;
	}
	return (max);
}

/*
** Devolve o no com o menor valor na stack.
*/
t_node	*stack_min(t_stack *s)
{
	t_node	*cur;
	t_node	*min;

	cur = s->top;
	min = cur;
	while (cur)
	{
		if (cur->value < min->value)
			min = cur;
		cur = cur->next;
	}
	return (min);
}
