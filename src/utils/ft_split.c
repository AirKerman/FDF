/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:00:20 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/27 16:13:27 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countword(char const *s, char sep)
{
	size_t	in_word;
	size_t	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != sep && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == sep && in_word)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_split_cpy(char const *s, char const *c)
{
	char	*str;
	size_t	i;
	size_t	lenstr;

	lenstr = c - s;
	str = ft_calloc(1, lenstr + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < lenstr)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	free_split(char	**arr, size_t arr_i)
{
	if (arr[arr_i] == NULL)
	{
		while (arr_i)
		{
			--arr_i;
			free(arr[arr_i]);
		}
		free(arr);
		return (1);
	}
	return (0);
}

static int	machine_split(char **arr, const char *s, char c)
{
	const char	*start;
	size_t		arr_i;

	arr_i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			arr[arr_i] = ft_split_cpy(start, s);
			if (free_split(arr, arr_i))
			{
				return (0);
			}
			arr_i++;
		}
		else
			s++;
	}
	arr[arr_i] = NULL;
	return (1);
}

int	*ft_split(char const *s, char c)
{
	int		*arr;
	size_t	word_c;

	word_c = countword(s, c) + 1;
	arr = ft_calloc(word_c, sizeof(char *));
	if (!arr)
		return (NULL);
	if (!machine_split(arr, s, c))
		return (NULL);
	return (arr);
}
/*
#include <stdio.h>

int main()
{
	int	i = 0;
	char	**arr = ft_split(",test,mot,aleatoire,",',');
	
	while (i < 5)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
*/
