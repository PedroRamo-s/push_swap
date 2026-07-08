/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/04 04:55:39 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*static int	log2_ceil(int n)
{
	int	result;
	int	power;

	result = 0;
	power = 1;
	while (power < n)
	{
		power *= 2;
		result++;
	}
	return (result);
}

*
** Push A→B em chunks de tamanho log2(n).
** Dentro de cada chunk escolhe sempre o de menor custo em A.
** Resultado: B tem ceil(n/log2(n)) grupos — O(n/log n) grupos.
*
static void	push_log_chunks(t_program *prog, int size)
{
	int		chunk_size;
	int		chunk_min;
	int		chunk_max;
	t_node	*best;

	chunk_size = log2_ceil(size);
	chunk_min = 0;
	chunk_max = chunk_size - 1;
	while (chunk_min < size && prog->a.size > 3)
	{
		while (1)
		{
			best = best_selector_a(&prog->a, chunk_max, chunk_min);
			if (!best)
				break ;
			rotate_to_top(&prog->a, best, prog);
			pb(prog);
		}
		chunk_min += chunk_size;
		chunk_max += chunk_size;
	}
}

*
** Dentro de cada chunk de B (tamanho log2(n)), os elementos têm
** índices contíguos. O drain pega sempre o máximo do chunk do topo
** usando rotate local em B — no máximo log2(n) rotações por elemento.
** Isso torna o drain O(n * log n) em vez de O(n²).
*
static t_node	*max_in_range(t_list *b, int idx_min, int idx_max)
{
	t_node	*tmp;
	t_node	*best;
	int		i;

	tmp = b->head;
	best = NULL;
	i = 0;
	while (i < b->size)
	{
		if (tmp->index >= idx_min && tmp->index <= idx_max)
		{
			if (!best || tmp->index > best->index)
				best = tmp;
		}
		tmp = tmp->next;
		i++;
	}
	return (best);
}

static void	drain_chunk(t_program *prog, int idx_min, int idx_max)
{
	t_node	*best;
	int		pos_a;
	int		ca;
	int		cb;
	int		pos_b;

	while (1)
	{
		best = max_in_range(&prog->b, idx_min, idx_max);
		if (!best)
			break ;
		pos_b = get_pos(&prog->b, best);
		pos_a = find_target_a(&prog->a, best->value);
		cb = signed_cost(pos_b, prog->b.size);
		ca = signed_cost(pos_a, prog->a.size);
		do_rotations(prog, ca, cb);
		pa(prog);
	}
}

static void	finalize_a(t_program *prog)
{
	t_node	*min;
	int		cost;

	min = stack_min(&prog->a);
	cost = signed_cost(get_pos(&prog->a, min), prog->a.size);
	while (cost > 0)
	{
		ra(prog);
		cost--;
	}
	while (cost < 0)
	{
		rra(prog);
		cost++;
	}
}

void	sort_complex(t_program *prog)
{
	int	size;
	int	chunk_size;
	int	idx_max;

	indexer(&prog->a);
	size = prog->a.size;
	chunk_size = log2_ceil(size);
	push_log_chunks(prog, size);
	sort_three(prog);
	idx_max = size - 1;
	while (idx_max >= 0)
	{
		drain_chunk(prog, idx_max - chunk_size + 1, idx_max);
		idx_max -= chunk_size;
	}
	finalize_a(prog);
}*/
