/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:11:45 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/12 04:47:36 by aantela-         ###   ########.fr       */
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

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}			t_stack;

typedef enum e_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strategy;

typedef struct s_config
{
	t_strategy	strategy;
	int			bench_mode;
}				t_config;

//ERRO_HANDLER.C
void	handle_error_and_exit(t_stack *stack);
void	free_stack(t_stack *stack);

//PARSE_ARGS.C
int		ft_atoi_safe(const char *str, int *result);
int		is_numeric(char *str);
int		has_duplicate(t_stack *stack, int value);
int		parse_flags(int argc, char **argv, t_config *config);

//PUSH_SWAP_UTILS.C
t_node	*node_builder(int value);
void	add_bottom(t_stack *stack, int value);
void	init_stack_a(t_stack *stack_a, int argc, char **argv, int start_index);

//UTILS
int	ft_strcmp(const char *s1, const char *s2);

void	sa(t_node **stack_a);
#endif
