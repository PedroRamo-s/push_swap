/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aantela- <aantela-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 03:33:19 by aantela-          #+#    #+#             */
/*   Updated: 2026/06/29 15:14:10 by aantela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*extract_word(const char *str, size_t start, size_t finish)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (finish - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*char	**ft_split(char const *s)
{
	char	**array;
	size_t	i;
	int		j;
	int		s_word;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	s_word = -1;
	while (s[i])
	{
		if (s[i] != ' ' && s_word < 0)
			s_word = i;
		else if ((s[i] == ' ' || s[i + 1] == '\0') && s_word >= 0)
		{
			if (s[i] != ' ')
				array[j++] = extract_word(s, s_word, i + 1);
			else
				array[j++] = extract_word(s, s_word, i);
			s_word = -1;
		}
		i++;
	}
	if (s_word >= 0)
		array[j++] = extract_word(s, s_word, i);
	array[j] = NULL;
	return (array);
}*/
char	**ft_split(char const *s)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	start;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != ' ')
				i++;
			array[j++] = extract_word(s, start, i);
		}
	}
	return (array[j] = NULL, array);
}
