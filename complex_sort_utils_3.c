/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:03:10 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/02 04:22:58 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
** Executa as rotações simultâneas (rr ou rrr) e depois as restantes.
** ca: custo signed de A, cb: custo signed de B.
*/
void	do_rotations(t_program *prog, int ca, int cb)
{
	while (ca > 0 && cb > 0)
	{
		rr(prog);
		ca--;
		cb--;
	}
	while (ca < 0 && cb < 0)
	{
		rrr(prog);
		ca++;
		cb++;
	}
	while (ca > 0)
	{
		ra(prog);
		ca--;
	}
	while (ca < 0)
	{
		rra(prog);
		ca++;
	}
	while (cb > 0)
	{
		rb(prog);
		cb--;
	}
	while (cb < 0)
	{
		rrb(prog);
		cb++;
	}
}

/*
** Roda A até a posição pos ficar no topo, depois faz pa.
*/
void	rotate_a_to_pos(t_program *prog, int pos_a)
{
	int	ca;

	ca = signed_cost(pos_a, prog->a.size);
	while (ca > 0)
	{
		ra(prog);
		ca--;
	}
	while (ca < 0)
	{
		rra(prog);
		ca++;
	}
}

/*
** Move o nó mais barato de B para a posição correta em A.
*/
void	move_cheapest(t_program *prog)
{
	t_node	*node;
	int		pos_b;
	int		pos_a;
	int		cb;
	int		ca;

	node = find_cheapest(&prog->a, &prog->b);
	pos_b = get_pos(&prog->b, node);
	pos_a = find_target_a(&prog->a, node->value);
	cb = signed_cost(pos_b, prog->b.size);
	ca = signed_cost(pos_a, prog->a.size);
	do_rotations(prog, ca, cb);
	pa(prog);
}
