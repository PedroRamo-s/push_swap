/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_medium.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:36:26 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/17 14:36:27 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int find_max_pos(t_stack *b)
{
    t_node  *curr;
    int     max_val;
    int     max_pos;
    int     curr_pos;

    curr = b->top;
    max_val = curr->value;
    max_pos = 0;
    curr_pos = 0;
    while (curr)
    {
        if (curr->value > max_val)
        {
            max_val = curr->value;
            max_pos = curr_pos;
        }
        curr_pos++;
        curr = curr->next;
    }
    return (max_pos);
}

int find_target_b(t_stack *b, int value_a)
{
    t_node  *curr;
    int     pos;

    curr = b->top;
    pos = 1;
    while (curr->next)
    {
        if (curr->value > value_a && curr->next->value < value_a)
            return (pos);
        pos++;
        curr = curr->next;
    }
    if (curr->value > value_a && b->top->value < value_a)
        return (0); 
    return (find_max_pos(b));
}