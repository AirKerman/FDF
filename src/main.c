/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:03:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/27 23:10:27 by rkerman          ###   ########.fr       */
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

int	file_checker(char *path, t_val *data)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		size = countwords(line);
		data->width = size;
		while (line)
		{
			if (!size || size != countwords(line) || !is_hex(line))
				return (free(line), 0);
			data->height++;
			free(line);
			line = get_next_line(fd);
		}
		data->size = data->width * data->height;
		close(fd);
		return (1);
	}
	return (0);
}

int	grid_fill(char *path, int ***grid, t_val *data)
{
	int	fd;
	char	**s;

	fd = open(path, O_RDONLY);
	*grid = ft_calloc(data->size + 1, sizeof(int *));
	if (!*grid)
		return (0);
	
}

int	file_processing(char *path, int ***grid, t_val *data)
{
	if (!file_checker(path, data) || !grid_fill(path, grid, data))
		return (0);
	return (1);
}

void	init_data(t_val *data)
{
	data->size = 0;
	data->width = 0;
	data->height = 0;
}

int	main(int argc, char **argv)
{
	int	**g;
	t_val data;

	init_data(&data);
	if ((argc - 1) == 1 && file_processing(argv[1], &g, &data))
	{
		printf("nombre d'element dans une ligne : %d\n", data.width);
		printf("hauteur de la grille : %d\n", data.height);
		printf("taille complete d'element : %d\n", data.size);
	}
	else
		write(2, "Error map\n", 10);
}
