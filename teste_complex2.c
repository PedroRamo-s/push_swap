/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_complex2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 02:59:41 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/19 03:00:35 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Roda A pelo custo assinado ca:
**   ca > 0 -> ra x ca vezes
**   ca < 0 -> rra x |ca| vezes
*/
static void	rotate_a(t_stack *a, t_stack *b, t_bench *bench, int ca)
{
	while (ca > 0)
	{
		ra(a, b, bench);
		ca--;
	}
	while (ca < 0)
	{
		rra(a, b, bench);
		ca++;
	}
}

/*
** Roda B pelo custo assinado cb.
*/
static void	rotate_b(t_stack *a, t_stack *b, t_bench *bench, int cb)
{
	while (cb > 0)
	{
		rb(b, a, bench);
		cb--;
	}
	while (cb < 0)
	{
		rrb(b, a, bench);
		cb++;
	}
}

/*
** Executa as rotacoes de A e B de forma optima:
** se ca e cb tiverem o mesmo sinal, usa rr/rrr (simultaneo)
** para a parte comum; depois roda o restante individualmente.
*/
void	do_rotations(t_stack *a, t_stack *b, t_bench *bench, int ca, int cb)
{
	while (ca > 0 && cb > 0)
	{
		rr(a, b, bench);
		ca--;
		cb--;
	}
	while (ca < 0 && cb < 0)
	{
		rrr(a, b, bench);
		ca++;
		cb++;
	}
	rotate_a(a, b, bench, ca);
	rotate_b(a, b, bench, cb);
}

/*
** Roda A ate o no na posicao pos (0-based) ficar no topo.
** Escolhe a direcao mais curta (ra ou rra).
*/
void	rotate_a_to_pos(t_stack *a, t_stack *b, t_bench *bench, int pos)
{
	int	dist;

	if (pos <= a->size / 2)
		dist = pos;
	else
		dist = pos - a->size;
	while (dist > 0)
	{
		ra(a, b, bench);
		dist--;
	}
	while (dist < 0)
	{
		rra(a, b, bench);
		dist++;
	}
}

/*
** Encontra o no mais barato, executa as rotacoes necessarias em A e B,
** e faz pb.
*/
void	move_cheapest(t_stack *a, t_stack *b, t_bench *bench)
{
	t_node	*node;
	int		pos_a;
	int		pos_b;
	int		ca;
	int		cb;

	node = find_cheapest(a, b);
	pos_a = get_pos(a, node);
	pos_b = find_target_b(b, node->value);
	ca = signed_cost(pos_a, a->size);
	cb = signed_cost(pos_b, b->size);
	do_rotations(a, b, bench, ca, cb);
	pb(a, b, bench);
}
