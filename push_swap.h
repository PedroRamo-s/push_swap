/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:11:45 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/10 05:13:25 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	struct s_node	*previous;
}					t_node;

//ERRO_HANDLES
void	error_exit(void);
void	free_stack(t_node **stack);

//PARSE_ARGS
int		ft_atoi_safe(const char *str, int *result);
int		is_numeric(char *str);
int		has_duplicate(t_node *stack_a, int value);

//PUSH_SWAP_UTILS
void	sa(t_node **stack_a);
t_node	*node_builder(int value);
void	append_node(t_node **stack, t_node *new_node);
int		init_stack_a(t_node **stack_a, int argc, char **argv)

#endif
