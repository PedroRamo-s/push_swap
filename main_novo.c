/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_novo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 04:48:56 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/24 21:54:13 by aantela-         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_program	prog;
	char		**split_args;
	int			j;
	int			value;

	if (argc < 2)
		return (0);
	prog = (t_program){0};
	parse_flags(argc, argv, &prog);
	if (prog.start_index > prog.end_index)
		return (0);
	while (prog.start_index <= prog.end_index)
	{
		split_args = ft_split(argv[prog.start_index]);
		if (!split_args || !split_args[0])
			cleanup_and_error(&prog, split_args);
		j = 0;
		while (split_args[j])
		{
			if (!is_numeric(split_args[j])
				|| ft_atoi_safe(split_args[j], &value) == 0
				|| has_duplicate(&prog.a, value))
				cleanup_and_error(&prog, split_args);
			create_and_add_bottom(&prog.a, value);
			j++;
		}
		free_array(split_args);
		prog.start_index++;
	}
	prog.disorder = compute_disorder(&prog.a);
	if (is_sorted(&prog.a))
	{
		free_stack(&prog.a);
		free_stack(&prog.b);
		return (0);
	}
	if (prog.strategy == STRAT_SIMPLE)
		sort_simple(&prog);//bom para desordem 0-10 || 90-100 n = 100 
	if (prog.strategy == STRAT_MEDIUM)
		sort_medium(&prog);
if (prog.bench_mode)
		print_bench(&prog, prog.disorder);
	free_stack(&prog.a);
	free_stack(&prog.b);
	return (0);
}
