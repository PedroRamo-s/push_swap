/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 18:48:43 by aantela-          #+#    #+#             */
/*   Updated: 2026/07/04 05:03:53 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	set_strategy(t_program *prog, t_strategy new_strat)
{
	if (prog->strategy != STRAT_NONE)
		return (0);
	prog->strategy = new_strat;
	return (1);
}

static t_strategy	flag_to_strategy(const char *flag)
{
	if (ft_strcmp(flag, "--simple") == 0)
		return (STRAT_SIMPLE);
	if (ft_strcmp(flag, "--medium") == 0)
		return (STRAT_MEDIUM);
	if (ft_strcmp(flag, "--complex") == 0)
		return (STRAT_COMPLEX);
	if (ft_strcmp(flag, "--adaptive") == 0)
		return (STRAT_ADAPTIVE);
	return (STRAT_NONE);
}

static int	parse_one_flag(const char *flag, t_program *prog)
{
	t_strategy	strat;

	if (ft_strcmp(flag, "--bench") == 0)
	{
		if (prog->bench_mode == 1)
			return (0);
		prog->bench_mode = 1;
		return (1);
	}
	strat = flag_to_strategy(flag);
	if (strat == STRAT_NONE)
		return (-1);
	if (!set_strategy(prog, strat))
		return (0);
	return (1);
}

static int	process_flags(int argc, char **argv, t_program *prog)
{
	int	res;

	while (prog->start_index < argc)
	{
		res = parse_one_flag(argv[prog->start_index], prog);
		if (res == -1)
			break ;
		if (res == 0)
			return (0);
		prog->start_index++;
	}
	while (prog->end_index >= prog->start_index)
	{
		res = parse_one_flag(argv[prog->end_index], prog);
		if (res == -1)
			break ;
		if (res == 0)
			return (0);
		prog->end_index--;
	}
	return (1);
}

int	parse_flags(int argc, char **argv, t_program *prog)
{
	prog->strategy = STRAT_NONE;
	prog->bench_mode = 0;
	prog->start_index = 1;
	prog->end_index = argc - 1;
	if (!process_flags(argc, argv, prog))
		return (0);
	if (prog->strategy == STRAT_NONE)
		prog->strategy = STRAT_ADAPTIVE;
	return (1);
}
