/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 04:02:40 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/03 04:06:07 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*strategy_name(t_strategy strategy)
{
	if (strategy == STRAT_SIMPLE)
		return ("Simple [O(n²)]");
	if (strategy == STRAT_MEDIUM)
		return ("Medium [O(n\\sqrt{n})]");
	if (strategy == STRAT_COMPLEX)
		return ("Complex [O(n log n)]");
	return ("Adaptive");
}
