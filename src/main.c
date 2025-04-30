/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:03:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:22:00 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	set_fdf(t_val *d)
{
	int	i;

	i = 0;
	while (i < 7)
	{
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

int	close_win(t_val *d)
{
	int	i;

	i = 0;
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->mlx_win);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	while (i < d->size)
	{
		free(d->grid[i]);
		i++;
	}
	free(d->grid);
	exit(0);
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
	mlx_hook(d->mlx_win, 2, 1L << 0, handler_hook, d);
	mlx_loop(d->mlx);
}

int	main(int argc, char **argv)
{
	t_val	data;

	init_data(&data);
	if ((argc - 1) == 1 && file_processing(argv[1], &data))
		fdf(&data);
	else
		write(2, "Error map\n", 10);
}
