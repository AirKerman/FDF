/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:03:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/24 23:59:17 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	countwords(char *str)
{
	int	c;
	int	in_w;

	c = 0;
	in_w = 0;
	while (*str)
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

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ',' || s[i] == ' '
		|| s[i] == '\n' || (s[i] >= '0' && s[i] <= '9')
		|| s[i] == '-' || (s[i] >= 'a' && s[i] <= 'f') || s[i] == 'x'
		|| (s[i] >= 'A' && s[i] <= 'F') || s[i] == 'X')
		i++;
	if (s[i] || !i)
	{
		printf("%c", s[i]);
		return (0);
	}
	return (1);
}

int	file_processing(char *path, int **grid)
{
	int	fd;
	char	*line;
	int	size;
	int	c;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		line = get_next_line(fd);
		size = countwords(line);
		while (line)
		{
			if (!size)
				size = countwords(line);
			if (size != countwords(line) || !is_num(line))
				return (free(line), 0);
			c++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		return (1);
	}
}

int	main(int argc, char **argv)
{
	int	*g;

	if ((argc - 1) == 1 && file_processing(argv[1], &g))
	{
	}
}
