/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_medium.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:36:26 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/25 15:20:26 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_rank(int *values, int size, int i)
{
	int j;
	int	rank;

	j = 0;
	rank = 0;
	while (j <size)
	{
		if (values[i] > values[j])
			rank++;
		j++;
	}
	return (rank);
}
void	index_assigner(t_list *stack, int *values)
{
	int		i;
	int		size;
	t_node	*tmp;

	i = 0;
	size = stack->size;
	tmp = stack->head;
	while (i < size)
	{
		tmp -> index = get_rank(values, size, i);
		tmp = tmp -> next;
		i++;
	}
}

void	indexer(t_list *stack)
{
	int	*values;
	printf("chegou no indexer \n");
	values = array_filler(stack);
	if (!values)
		return ;
	index_assigner(stack, values);
	free(values);
}

int	ft_sqrt(int nb)
{
	int	i;
	printf("chamou sei la quem de ft_sqrt\n");
	i = 1;
	while (i * i <= nb)
	{
		if (i * i == nb)
		{
			return (i);
		}
		i++;
	}
	return (i - 1);
}
