/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:02:04 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:38:21 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_p(t_val *data, int x, int y, int c)
{
	char	*dst;

	if (x >= 0 && x <= SIZE_W && y >= 0 && y <= SIZE_H)
	{
		dst = data->addr + (y * data->lw + x * (data->bpp / 8));
		*(unsigned int *)dst = c;
	}
}

void	free_all(int **g)
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

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
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
