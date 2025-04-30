/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:44:53 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:41:59 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	countwords(char *str)
{
	int	c;
	int	in_w;

	c = 0;
	in_w = 0;
	while (str && *str)
	{
		if (!in_w && *str != ' ')
		{
			in_w = 1;
			c++;
		}
		else if (*str == ' ')
			in_w = 0;
		str++;
	}
	return (c);
}

int	ft_atoi(char *s)
{
	int	c;
	int	n;

	c = 0;
	n = 1;
	while (s && *s == ' ')
		s++;
	if (s && (*s == '-' || *s == '+'))
	{
		if (*s == '-')
			n = -1;
		s++;
	}
	while (s && (*s >= '0' && *s <= '9'))
	{
		c = (c * 10) + (*s - '0');
		s++;
	}
	return (c * n);
}

int	c_sch(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_hex(char *s)
{
	int	i;

	i = 0;
	while (s && (s[i] == ',' || s[i] == ' '
			|| s[i] == '\n' || (s[i] >= '0' && s[i] <= '9')
			|| s[i] == '-' || (s[i] >= 'a' && s[i] <= 'f') || s[i] == 'x'
			|| (s[i] >= 'A' && s[i] <= 'F') || s[i] == 'X'))
		i++;
	if (s[i] || !i)
		return (0);
	return (1);
}

int	ft_hextoi(char *s, int len)
{
	int	c;

	c = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			c = (c * len) + (*s - '0');
		else if (*s >= 'a' && *s <= 'f')
			c = (c * len) + (*s - 'a' + 10);
		else if (*s >= 'A' && *s <= 'F')
			c = (c * len) + (*s - 'A' + 10);
		s++;
	}
	return (c);
}
