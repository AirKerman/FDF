/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:03:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/29 02:54:50 by rkerman          ###   ########.fr       */
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

void free_all(int **g)
{
	int	i;

	i = 0;
	while (g[i])
	{
		free(g[i]);
		i++;	
	}
	free(g);
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
int	grid_fill(char *path, t_val *data)
{
	int		fd;
	char	**s;
	char	*l;
	int		x;
	int		y;
	int		i;

	fd = open(path, O_RDONLY);
	data->grid = ft_calloc(data->size + 5, sizeof(int *));
	if (!data->grid)
		return (0);
	l = get_next_line(fd);
	y = 0;
	i = 0;
	while (l)
	{
		x = 0;
		s = ft_split(l, ' ');
		if (!s)
		{
			free_all(data->grid);
			return (0);
		}
		while (s[x])
		{
			data->grid[i] = ft_calloc(5, sizeof(int));
			if (!data->grid[i])
			{
				free_all(data->grid);
				return (0);
			}
			data->grid[i][0] = x * MULTI;
			data->grid[i][1] = y * MULTI;
			data->grid[i][2] = ft_atoi(s[x]) * MULTI;
			if (c_sch(s[x], ',') != -1)
				data->grid[i][3] = ft_hextoi(&s[x][c_sch(s[x], 'x')], 16);
			else
				data->grid[i][3] = COLOR;
			x++;
			i++;
		}
		y++;
		free(l);
		l = get_next_line(fd);
	}
	return (1);	
}

int	file_processing(char *path, t_val *data)
{
	if (!file_checker(path, data) || !grid_fill(path, data))
		return (0);
	return (1);
}

void	init_data(t_val *data)
{
	data->size = 0;
	data->width = 0;
	data->height = 0;
}

/*
void	bresenham()
{
	int	d;

	d = y + y - x;

}
*/
void	put_p(t_val *data, int x, int y, int c)
{
	char	*dst;

	if (x >= 0 && x <= 1920 && y >= 0 && y <= 1920)
	{
		dst = data->addr + (y * data->lw + x * (data->bpp / 8));
		*(unsigned int*)dst = c;
	}
}

void	display_fdf(t_val *d)
{
	int	i;

	i = 0;
	while (i < d->size)
	{
		printf("%d\n", i);
		put_p(d, d->grid[i][0], d->grid[i][1], 0xFFFFFF);
		i++;
	}
}

void	fdf(t_val *d)
{
	void	*mlx;
	void	*mlx_win;
	(void)d;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Fil 2 Fer");
	d->img = mlx_new_image(mlx, 1920, 1080);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->lw, &d->endian);
	display_fdf(d);
	mlx_put_image_to_window(mlx, mlx_win, d->img, 0, 0);
	mlx_loop(mlx);

}

int	main(int argc, char **argv)
{
	t_val data;

	init_data(&data);
	if ((argc - 1) == 1 && file_processing(argv[1], &data))
		fdf(&data);
	else
		write(2, "Error map\n", 10);
	
}
