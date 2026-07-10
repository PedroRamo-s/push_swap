/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_novo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 04:48:56 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/10 03:23:35 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	cleanup_and_error(t_program *prog, char **split_args)
{
	free_array(split_args);
	free_stack(&prog->a);
	free_stack(&prog->b);
	write(2, "Error\n", 6);
	exit(1);
}

static void	parse_one_arg(t_program *prog, char **split_args)
{
	int	j;
	int	value;

	j = 0;
	while (split_args[j])
	{
		if (!is_numeric(split_args[j])
			|| ft_atoi_safe(split_args[j], &value) == 0
			|| has_duplicate(&prog->a, value))
			cleanup_and_error(prog, split_args);
		create_and_add_bottom(&prog->a, value);
		j++;
	}
}

static void	parse_args(t_program *prog, char **argv)
{
	char	**split_args;

	while (prog->start_index <= prog->end_index)
	{
		split_args = ft_split(argv[prog->start_index]);
		if (!split_args || !split_args[0])
			cleanup_and_error(prog, split_args);
		parse_one_arg(prog, split_args);
		free_array(split_args);
		prog->start_index++;
	}
}

static void	resolve_and_sort(t_program *prog)
{
	if (prog->strategy == STRAT_ADAPTIVE)
	{
		if (prog->disorder < 0.2)
		{
			simple_sort(prog);
			prog->adaptive = STRAT_SIMPLE;
		}
		else if (prog -> disorder >= 0.2 && prog->disorder < 0.5)
		{
			medium_sort(prog);
			prog->adaptive = STRAT_MEDIUM;
		}
		else
		{
			complex_sort(prog);
			prog->adaptive = STRAT_COMPLEX;
		}
	}
	if (prog->strategy == STRAT_SIMPLE)
		simple_sort(prog);
	if (prog->strategy == STRAT_MEDIUM)
		medium_sort(prog);
	if (prog->strategy == STRAT_COMPLEX)
		complex_sort(prog);
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (argc < 2)
		return (0);
	prog = (t_program){0};
	parse_flags(argc, argv, &prog);
	if (prog.start_index > prog.end_index)
		return (0);
	parse_args(&prog, argv);
	prog.disorder = compute_disorder(&prog.a);
	if (is_sorted(&prog.a))
	{
		free_all_stack(&prog);
		if (prog.bench_mode)
			print_bench(&prog, prog.disorder);
		return (0);
	}
	else
		resolve_and_sort(&prog);
	if (prog.bench_mode)
		print_bench(&prog, prog.disorder);
	free_all_stack(&prog);
	return (0);
}
