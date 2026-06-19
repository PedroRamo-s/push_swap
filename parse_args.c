/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:59:48 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/13 05:27:37 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/**
 * @brief Converte uma string para inteiro com proteção contra overflow.
 * @param str A string a ser convertida (já validada pela sintaxe).
 * @param result Ponteiro onde o int final será guardado.
 * @return 1 se a conversão for bem-sucedida, 0 se houver overflow/underflow.
 */
int	ft_atoi_safe(const char *str, int *result)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		if (sign == 1 && res > INT_MAX)
			return (0);
		if (sign == -1 && (-res) < INT_MIN)
			return (0);
		i++;
	}
	*result = (int)(res * sign);
	return (1);
}

int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicate(t_stack *stack, int value)
{
	t_node *current;

	if (!stack || !stack -> top)
		return (0);
	current = stack -> top;
	while (current)
	{
		if (current -> value == value)
			return (1);
		current = current -> next;
	}
	return (0);
}

int	parse_flags(int	argc, char **argv, t_config *config)
{
	int	i;

	i = 1;
	config -> strategy = STRAT_ADAPTIVE;
	config -> bench_mode = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
			config -> bench_mode = 1;
		else if (ft_strcmp(argv[i], "--simple") == 0)
			config -> strategy = STRAT_SIMPLE;
		else if (ft_strcmp(argv[i], "--medium") == 0)
			config -> strategy = STRAT_MEDIUM;
		else if (ft_strcmp(argv[i], "--complex") == 0)
			config -> strategy = STRAT_COMPLEX;
		else if (ft_strcmp(argv[i], "--adaptative") == 0)
			config -> strategy = STRAT_ADAPTIVE;
		else
			break ;
		i++;
	}
	return (i);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack -> top || stack -> size < 2)
		return (1);
	current = stack -> top;
	while (current -> next != NULL)
	{
		if (current -> value > current -> next -> value)
			return (0);
		current = current -> next;
	}
	return (1);
}
