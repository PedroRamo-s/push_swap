/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:56:16 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/03 04:59:35 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*copy_stack_to_array(t_list *a)
{
	int		*arr;
	t_node	*current;
	int		i;

	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		return (NULL);
	current = a->head;
	i = 0;
	while (current && i < a->size)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	return (arr);
}

static void	copy_back(int *arr, int *temp, t_range range)
{
	int	i;

	i = range.l;
	while (i <= range.r)
	{
		arr[i] = temp[i];
		i++;
	}
}

static long long	merge_and_count(int *arr, int *temp, t_range range)
{
	int			i;
	int			j;
	int			k;
	long long	inv_count;

	i = range.l;
	j = range.m + 1;
	k = range.l;
	inv_count = 0;
	while (i <= range.m && j <= range.r)
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
		{
			temp[k++] = arr[j++];
			inv_count += (range.m - i + 1);
		}
	}
	while (i <= range.m)
		temp[k++] = arr[i++];
	while (j <= range.r)
		temp[k++] = arr[j++];
	copy_back(arr, temp, range);
	return (inv_count);
}

static long long	count_inversions(int *arr, int *temp, t_range range)
{
	long long	inv_count;
	t_range		left;
	t_range		right;

	inv_count = 0;
	if (range.l < range.r)
	{
		range.m = range.l + (range.r - range.l) / 2;
		left = (t_range){range.l, 0, range.m};
		right = (t_range){range.m + 1, 0, range.r};
		inv_count += count_inversions(arr, temp, left);
		inv_count += count_inversions(arr, temp, right);
		inv_count += merge_and_count(arr, temp, range);
	}
	return (inv_count);
}

double	compute_disorder(t_list *a)
{
	int			*arr;
	int			*temp;
	long long	mistakes;
	double		total_pairs;
	t_range		range;

	if (!a || a->size < 2)
		return (0.0);
	arr = copy_stack_to_array(a);
	temp = malloc(sizeof(int) * a->size);
	if (!arr || !temp)
	{
		free(arr);
		free(temp);
		return (0.0);
	}
	range = (t_range){0, 0, a->size - 1};
	mistakes = count_inversions(arr, temp, range);
	total_pairs = ((double)a->size * (a->size - 1)) / 2.0;
	free(arr);
	free(temp);
	return ((double)mistakes / total_pairs);
}
