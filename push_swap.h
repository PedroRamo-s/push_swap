/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:11:45 by pgois-wa          #+#    #+#             */
/*   Updated: 2026/06/21 18:56:00 by aantela-         ###   ########.fr       */
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
	STRAT_COMPLEX,
	STRAT_NONE
}	t_strategy;

typedef struct	s_bench
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int ra;
	int rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}		t_bench;

typedef struct s_program
{
	t_stack		a;
	t_stack		b;
	t_bench		bench;
	t_strategy	strategy;
	int			bench_mode;
	int			start_index;
	int			end_index;
	double		disorder;
}				t_program;

// DEGUG TOOLS
void	print_stacks(const char *op, t_stack *a, t_stack *b);

//ERRO_HANDLER.C
void	handle_error_and_exit(t_stack *stack);
void	free_stack(t_stack *stack);

//PARSE_ARGS.C
int		ft_atoi_safe(const char *str, int *result);
int		is_numeric(char *str);
int		has_duplicate(t_stack *stack, int value);
int		parse_flags(int argc, char **argv, t_program *prog);
int		is_sorted(t_stack *stack);

//PUSH_SWAP_UTILS.C
t_node	*node_builder(int value);
void	add_bottom(t_stack *stack, int value);
void	init_stack_a(t_stack *stack_a, int argc, char **argv, int start_index);

//UTILS
int	ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s);
void	free_array(char **array);

// operadores
// adicionado a sa e sb stack temporarias para debug.
void	sa(t_stack *a, t_stack *b, t_bench *bench);
void	sb(t_stack *b, t_stack *a, t_bench *bench);
void	ss(t_stack *a, t_stack *b, t_bench *bench);
//adicionado a ra e rb stack temporarias para debug.
void    ra(t_stack *a, t_stack *b, t_bench *bench);
void    rb(t_stack *b, t_stack *a, t_bench *bench);
void    rr(t_stack *a, t_stack *b, t_bench *bench);
//adicioonado a rra rrb stack temporarias para debug.
void	rra(t_stack *a, t_stack *b, t_bench *bench);
void	rrb(t_stack *b, t_stack *a, t_bench *bench);
void	rrr(t_stack *a, t_stack *b, t_bench *bench);


void	pa(t_stack *a, t_stack *b, t_bench *bench);
void	pb(t_stack *a, t_stack *b, t_bench *bench);

// simple sort teste
void	sort_three(t_stack *a, t_stack *b, t_bench *bench);
void	sort_simple(t_stack *a, t_stack *b, t_bench *bench);
// complex teste
int	get_pos(t_stack *s, t_node *target);
int	signed_cost(int pos, int size);
int	compute_total(int ca, int cb);
t_node	*stack_max(t_stack *s);
t_node	*stack_min(t_stack *s);
int	find_target_b(t_stack *b, int val);
int	find_target_a(t_stack *a, int val);
int	node_cost(t_stack *a, t_stack *b, t_node *node);
t_node	*find_cheapest(t_stack *a, t_stack *b);
void	do_rotations(t_stack *a, t_stack *b, t_bench *bench, int ca, int cb);
void	rotate_a_to_pos(t_stack *a, t_stack *b, t_bench *bench, int pos);
void	move_cheapest(t_stack *a, t_stack *b, t_bench *bench);
// BENCH
double	compute_disorder(t_stack *a);
void	print_bench(t_bench *bench, t_program *prog, double disorder);
#endif
