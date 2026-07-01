/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:56:16 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/01 05:06:14 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *copy_stack_to_array(t_list *a)
{
    int     *arr;
    t_node  *current;
    int     i;

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

static long long merge_and_count(int *arr, int *temp, int left, int mid, int right)
{
    int         i = left;
    int         j = mid + 1;
    int         k = left;
    long long   inv_count = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
        {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
    return (inv_count);
}

static long long count_inversions(int *arr, int *temp, int left, int right)
{
    long long inv_count = 0;
    int       mid;

    if (left < right)
    {
        mid = left + (right - left) / 2;
        inv_count += count_inversions(arr, temp, left, mid);
        inv_count += count_inversions(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    return (inv_count);
}

double compute_disorder(t_list *a)
{
    int         *arr;
    int         *temp;
    long long   mistakes;
    double      total_pairs;

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
    mistakes = count_inversions(arr, temp, 0, a->size - 1);
    total_pairs = ((double)a->size * (a->size - 1)) / 2.0;
    free(arr);
    free(temp);
    return ((double)mistakes / total_pairs);
}

char  *strategy_name(t_strategy strategy)
{
    if (strategy == STRAT_SIMPLE)
        return ("simple [O(n²)]");
    if (strategy == STRAT_MEDIUM)
        return ("medium [O(n\\sqrt{n})]");
    if (strategy == STRAT_COMPLEX)
        return ("complex [O(n log n)]");
    return ("Adaptive");
}

