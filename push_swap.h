/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgois-wa <pgois-wa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:11:45 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/05 15:11:46 by pgois-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	struct s_node	*previous;
}					t_node;

void	sa(t_node **stack_a);
t_node	*node_builder(int value);
