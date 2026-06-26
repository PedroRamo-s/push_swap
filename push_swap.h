/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:11:45 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/17 05:45:09 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*previous;
}					t_node;

typedef struct s_move_plan
{
	int				moves_a;
	int				direction_a;
	int				moves_b;
	int				direction_b;
	int				total_cost;
	t_node			*target_a;
}					t_move_plan;

typedef struct s_stack
{
	t_node			*top;
	t_node			*bottom;
	int				size;
}					t_stack;

typedef enum e_strategy
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}					t_strategy;

typedef struct s_bench
{
	int				sa;
	int				sb;
	int				ss;
	int				pa;
	int				pb;
	int				ra;
	int				rb;
	int				rr;
	int				rra;
	int				rrb;
	int				rrr;
}					t_bench;

typedef struct s_config
{
	t_strategy		strategy;
	int				bench_mode;
}					t_config;
// DEGUG TOOLS
void				print_stacks(const char *op, t_stack *a, t_stack *b);

// ERRO_HANDLER.C
void				handle_error_and_exit(t_stack *stack);
void				free_stack(t_stack *stack);

// PARSE_ARGS.C
int					ft_atoi_safe(const char *str, int *result);
int					is_numeric(char *str);
int					has_duplicate(t_stack *stack, int value);
int					parse_flags(int argc, char **argv, t_config *config);
int					is_sorted(t_stack *stack);

// PUSH_SWAP_UTILS.C
t_node				*node_builder(int value);
void				add_bottom(t_stack *stack, int value);
void				init_stack_a(t_stack *stack_a, int argc, char **argv,
						int start_index);
void				selection_plan(t_stack *stack, t_move_plan *plan);
void				plan_executor(t_stack *a, t_stack *b, t_move_plan *plan,
						t_bench *bench);

// PUSH_SWAP_UTILS_2.c

int					find_max_pos(t_stack *b);
int					find_target_b(t_stack *b, int value_a);

// UTILS
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s);
void				free_array(char **array);
void				rotate_to_top(t_stack *a, t_stack *b, t_node *target,
						t_bench *bench);
int					*array_filler(t_stack *stack);

// MEDIUM_UTILS

void				index_assigner(t_stack *stack, int *values);
void				indexer(t_stack *stack);
int					chunk_count(int size);
int					cost_calculator(int position, int stack_size);

// operadores
// adicionado a sa e sb stack temporarias para debug.
void				sa(t_stack *a, t_stack *b, t_bench *bench);
void				sb(t_stack *b, t_stack *a, t_bench *bench);
void				ss(t_stack *a, t_stack *b, t_bench *bench);
// adicionado a ra e rb stack temporarias para debug.
void				ra(t_stack *a, t_stack *b, t_bench *bench);
void				rb(t_stack *b, t_stack *a, t_bench *bench);
void				rr(t_stack *a, t_stack *b, t_bench *bench);
// adicioonado a rra rrb stack temporarias para debug.
void				rra(t_stack *a, t_stack *b, t_bench *bench);
void				rrb(t_stack *b, t_stack *a, t_bench *bench);
void				rrr(t_stack *a, t_stack *b, t_bench *bench);

void				pa(t_stack *a, t_stack *b, t_bench *bench);
void				pb(t_stack *a, t_stack *b, t_bench *bench);

// simple sort teste
void				sort_simple(t_stack *a, t_stack *b, t_bench *bench);
void				sort_medium(t_stack *a, t_stack *b, t_bench *bench);

// BENCH
double				compute_disorder(t_stack *a);
void				print_bench(t_bench *bench, t_config *config,
						double disorder);
#endif
