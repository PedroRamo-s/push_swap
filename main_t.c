/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 14:56:24 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/17 05:46:39 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_bench		bench;
	t_stack		stack_a;
	t_stack		stack_b;
	int			start_index;
	char		**split_args;
	int			split_count;
	double		disorder;

	if (argc < 2)
		return (0);
	bench = (t_bench) {0};
	start_index = parse_flags(argc, argv, &config);
	if (start_index == argc)
		return (0);
	stack_a.top = NULL;
	stack_a.bottom = NULL;
	stack_a.size = 0;
	stack_b.top = NULL;
	stack_b.bottom = NULL;
	stack_b.size = 0;
	if (start_index == argc - 1)
	{
		split_args = ft_split(argv[start_index]);
		if (!split_args || !split_args[0])
		{
			free_array(split_args);
			return (0);
		}
		split_count = 0;
		while (split_args[split_count])
			split_count++;
		while (split_count > 0)
		{
			split_count--;
			if (!is_numeric(split_args[split_count]))
			{
				free_array(split_args);
				handle_error_and_exit(&stack_a);
			}
		}
		split_count = 0;
		while (split_args[split_count])
		{
			int	value;
			if (ft_atoi_safe(split_args[split_count], &value) == 0)
			{
				free_array(split_args);
				handle_error_and_exit(&stack_a);
			}
			if (has_duplicate(&stack_a, value))
			{
				free_array(split_args);
				handle_error_and_exit(&stack_a);
			}
			add_bottom(&stack_a, value);
			split_count++;
		}
		free_array(split_args);
	}
	else
		init_stack_a(&stack_a, argc, argv, start_index);
	if (is_sorted(&stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	disorder = compute_disorder(&stack_a);
	if (config.strategy == STRAT_SIMPLE)
		sort_simple(&stack_a, &stack_b, &bench);
	if(config.strategy == STRAT_MEDIUM)
		sort_medium(&stack_a, &stack_b, &bench);
	if (config.bench_mode)
    print_bench(&bench, &config, disorder);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
