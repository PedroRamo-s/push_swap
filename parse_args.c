/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:59:48 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/10 05:09:03 by aantela-         ###   ########.fr       */
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
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] > '0' && str[i] < '9'))
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
		if (str[i] < '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicate(t_node *stack_a, int value)
{
	if (!stack_a)
		return (0);
	while (stack_a != NULL)
	{
		if (stack_a->value == value)
			return (1);
		stack_a = stack_a->next;
	}
	return (0);
}
