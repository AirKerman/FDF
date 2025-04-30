/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:58 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:49:47 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	grid_fill_bis(t_fill *v, t_val *data)
{
	while (v->s[v->x])
	{
		data->grid[v->i] = ft_calloc(5, sizeof(int));
		if (!data->grid[v->i])
			return (free_all(data->grid), 0);
		data->grid[v->i][0] = v->x * MULTI;
		data->grid[v->i][1] = v->y * MULTI;
		data->grid[v->i][2] = ft_atoi(v->s[v->x]) * Z_MULTI;
		if (c_sch(v->s[v->x], ',') != -1)
			data->grid[v->i][3] = ft_hextoi(&v->s[v->x][c_sch(v->s[v->x],
						'x')], 16);
		else
			data->grid[v->i][3] = COLOR;
		v->x++;
		v->i++;
	}
	v->y++;
	free(v->l);
	v->x = 0;
	while (v->s[v->x])
	{
		free(v->s[v->x]);
		v->x++;
	}
	return (1);
}

int	grid_fill(char *path, t_val *data)
{
	t_fill	vars;

	vars.fd = open(path, O_RDONLY);
	data->grid = ft_calloc(data->size + 5, sizeof(int *));
	if (!data->grid)
		return (0);
	vars.l = get_next_line(vars.fd);
	vars.y = 0;
	vars.i = 0;
	while (vars.l)
	{
		vars.x = 0;
		vars.s = ft_split(vars.l, ' ');
		if (!vars.s)
		{
			free_all(data->grid);
			return (0);
		}
		if (!grid_fill_bis(&vars, data))
			return (0);
		free(vars.s);
		vars.l = get_next_line(vars.fd);
	}
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

int	file_processing(char *path, t_val *data)
{
	if (!file_checker(path, data) || !grid_fill(path, data))
		return (0);
	return (1);
}

int	handler_hook(int keycode, t_val *d)
{
	if (keycode == 65307)
		close_win(d);
	return (0);
}
