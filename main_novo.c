/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_novo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 04:48:56 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/21 20:00:01 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_program	prog;
	char		**split_args;
	int			j;
	int			value;

	if (argc < 2)
		return (0);
	prog = (t_program) {0}; // Inicializa tudo a zero/NULL
	parse_flags(argc, argv, &prog);
	if (prog.start_index > prog.end_index)
		return (0);
	while (prog.start_index <= prog.end_index)
	{
		split_args = ft_split(argv[prog.start_index]);
		if (!split_args || !split_args[0])
		{
			free_array(split_args);
			handle_error_and_exit(&prog.a);
			handle_error_and_exit(&prog.b);
		}
		j = 0;
		while (split_args[j])
		{
			if (!is_numeric(split_args[j]) || 
				ft_atoi_safe(split_args[j], &value) == 0 || 
				has_duplicate(&prog.a, value))
			{
				free_array(split_args);
				handle_error_and_exit(&prog.a);
				handle_error_and_exit(&prog.b);
			}
			add_bottom(&prog.a, value);
			j++;
		}
		free_array(split_args);
		prog.start_index++;
	}
	if (is_sorted(&prog.a))
	{
		free_stack(&prog.a);
		return (0);
	}
	prog.disorder = compute_disorder(&prog.a);
	if (prog.strategy == STRAT_SIMPLE || prog.strategy == STRAT_ADAPTIVE)
		sort_simple(&prog.a, &prog.b, &prog.bench);
	if (prog.bench_mode)
		print_bench(&prog.bench, &prog, prog.disorder);// usando &prog.a, &prog.b, &prog.bench
	free_stack(&prog.a);
	free_stack(&prog.b);
	return (0);
}
