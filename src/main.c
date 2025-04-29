/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:03:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/29 19:37:38 by rkerman          ###   ########.fr       */
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

void    put_p(t_val *data, int x, int y, int c)
{
    char    *dst;

    if (x >= 0 && x <= SIZE_W && y >= 0 && y <= SIZE_H)
    {
        dst = data->addr + (y * data->lw + x * (data->bpp / 8));
        *(unsigned int*)dst = c;
    }
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
			data->grid[i][2] = ft_atoi(s[x]) * Z_MULTI;
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

void    rotate_x(int **tab, int size_tab)
{
    int i;  
    float   x;
    float   z;

    i = 0;
    while (i < size_tab)
    {
        x = (tab[i][0] * cos(ROTATESPEED)) - (tab[i][1] * sin(ROTATESPEED));
        z = (tab[i][0] * sin(ROTATESPEED)) + (tab[i][1] * cos(ROTATESPEED));
        tab[i][0] = x;
        tab[i][1] = z;
        i ++;
    }
}

void	r_rotate_x(int **tab, int size_tab)
{
	int	i;
	float	x;
	float	z;

	i = 0;
	while (i < size_tab)
	{
		x = (tab[i][0] * cos(-ROTATESPEED)) - (tab[i][1] * sin(-ROTATESPEED));
		z = (tab[i][0] * sin(-ROTATESPEED)) + (tab[i][1] * cos(-ROTATESPEED));
		tab[i][0] = x;
		tab[i][1] = z;
		i ++;
	}
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void bresenham(t_val *d, int *p1, int *p2)
{
    t_bre box;
    int x = p1[0];
    int y = p1[1];
    int color = p1[3];

    box.dx = p2[0] - x;
    box.dy = p2[1] - y;
    box.sx = (box.dx >= 0) ? 1 : -1;
    box.sy = (box.dy >= 0) ? 1 : -1;
    box.dx = (box.dx >= 0) ? box.dx : -box.dx;
    box.dy = (box.dy >= 0) ? box.dy : -box.dy;
    box.err = (box.dx > box.dy ? box.dx : -box.dy) / 2;

    while (1)
    {
        put_p(d, x + d->w_lag, y + d->h_lag, color);
        if (x == p2[0] && y == p2[1])
            break;
        box.e2 = box.err;
        if (box.e2 > -box.dx) {
            box.err -= box.dy;
            x += box.sx;
        }
        if (box.e2 < box.dy) {
            box.err += box.dx;
            y += box.sy;
        }
    }
}

void	r_rotate_y(int **tab, int size_tab)
{
	int	i;
	float	x;
	float	z;

	i = 0;
	while (i < size_tab)
	{
		x = (tab[i][0] * cos(-ROTATESPEED)) - (tab[i][2] * sin(-ROTATESPEED));
		z = (tab[i][0] * sin(-ROTATESPEED)) + (tab[i][2] * cos(-ROTATESPEED));
		tab[i][0] = x;
		tab[i][2] = z;
		i++;
	}
}

void	r_rotate_z(int **tab, int size_tab)
{
	int	i;
	float	x;
	float	z;

	i = 0;
	while (i < size_tab)
	{
		x = (tab[i][1] * cos(-ROTATESPEED)) - (tab[i][2] * sin(-ROTATESPEED));
		z = (tab[i][1] * sin(-ROTATESPEED)) + (tab[i][2] * cos(-ROTATESPEED));
		tab[i][1] = x;
		tab[i][2] = z;
		i ++;
	}
}

void    rotate_y(int **tab, int size_tab)
{
    int i;
    float   x;
    float   z;

    i = 0;
    while (i < size_tab)
    {
        x = (tab[i][0] * cos(ROTATESPEED)) - (tab[i][2] * sin(ROTATESPEED));
        z = (tab[i][0] * sin(ROTATESPEED)) + (tab[i][2] * cos(ROTATESPEED));
        tab[i][0] = x;
        tab[i][2] = z;
        i++;
    }
}

void    rotate_z(int **tab, int size_tab)
{
    int i;
    float   x;
    float   z;

    i = 0;
    while (i < size_tab)
    {
        x = (tab[i][1] * cos(ROTATESPEED)) - (tab[i][2] * sin(ROTATESPEED));
        z = (tab[i][1] * sin(ROTATESPEED)) + (tab[i][2] * cos(ROTATESPEED));
        tab[i][1] = x;
        tab[i][2] = z;
        i ++;
    }
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
	data->w_lag = SIZE_W / 2;
	data->h_lag = SIZE_H / 2;
	data->multi = 2;
}

void	display_fdf(t_val *d)
{
	int	i;

	i = 0;
	while (i < d->size - 1)
	{
		if ((i + 1) % d->width != 0)
			bresenham(d, d->grid[i], d->grid[i + 1]);
		i++;
	}
	i = 0;
	while (i < d->size - d->width)
	{
		bresenham(d, d->grid[i], d->grid[i + d->width]);
		i ++;
	}
}

void	mult_tab(t_val *d)
{
	int	i;

	i = 0;
	while (i < d->size)
	{
		d->grid[i][0] *= 0.9;
		d->grid[i][1] *= 0.9;
		d->grid[i][2] *= 0.9;
		i++;
	}
}

void	set_fdf(t_val *d)
{
	int	i;

	i = 0;
	while (i < 7)
	{
	//	r_rotate_x(d->grid, d->size);
		rotate_y(d->grid, d->size);
		rotate_z(d->grid, d->size);
		i++;
	}
	i = 0;
	while (d->grid[0][0] + d->w_lag < 500)
	{
		mult_tab(d);
	}
}
void	print_grid(t_val *d)
{
	int	i;

	i = 0;
	while (i < d->size)
	{
		printf("point numero %d x: %d, y: %d, z: %d\n", i, d->grid[i][0], d->grid[i][1], d->grid[i][2]);
		i++;
	}
}

void	center_grid(t_val *d)
{
	int	i;

	i = 0;
	while (i < d->size)
	{
		d->grid[i][0] -= d->width * MULTI / 2;
		d->grid[i][1] -= d->height * MULTI / 2;
		i++;
	}
}

int	close_win(int keycode, t_val *d)
{
	mlx_destroy_window(d->mlx, d->mlx_win);
	return (0);
}

void	fdf(t_val *d)
{
	d->mlx = mlx_init();
	center_grid(d);
	d->mlx_win = mlx_new_window(d->mlx, SIZE_W, SIZE_H, "Fil 2 Fer");
	d->img = mlx_new_image(d->mlx, SIZE_W, SIZE_H);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->lw, &d->endian);
	set_fdf(d);
	display_fdf(d);
	mlx_put_image_to_window(d->mlx, d->mlx_win, d->img, 0, 0);
	mlx_hook(d->mlx_win, 17, 0, close_win, d);
	mlx_loop(d->mlx);

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
