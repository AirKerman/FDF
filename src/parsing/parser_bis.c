/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:20:57 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:50:16 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_data(t_val *data)
{
	data->size = 0;
	data->width = 0;
	data->height = 0;
	data->w_lag = SIZE_W / 2;
	data->h_lag = SIZE_H / 2;
	data->multi = 2;
}

void	bresenham_choice(t_bre *box, int *p1, int *p2)
{
	box->y = p1[1];
	box->x = p1[0];
	box->dx = p2[0] - box->x;
	box->dy = p2[1] - box->y;
	if (box->dx >= 0)
		box->sx = 1;
	else
		box->sx = -1;
	if (box->dy >= 0)
		box->sy = 1;
	else
		box->sy = -1;
	if (box->dx >= 0)
		box->dx = box->dx;
	else
		box->dx = -box->dx;
	if (box->dy >= 0)
		box->dy = box->dy;
	else
		box->dy = -box->dy;
	if (box->dx > box->dy)
		box->err = box->dx / 2;
	else
		box->err = -box->dy / 2;
}

void	bresenham(t_val *d, int *p1, int *p2)
{
	t_bre	box;

	bresenham_choice(&box, p1, p2);
	while (1)
	{
		put_p(d, box.x + d->w_lag, box.y + d->h_lag, p1[3]);
		if (box.x == p2[0] && box.y == p2[1])
			break ;
		box.e2 = box.err;
		if (box.e2 > -box.dx)
		{
			box.err -= box.dy;
			box.x += box.sx;
		}
		if (box.e2 < box.dy)
		{
			box.err += box.dx;
			box.y += box.sy;
		}
	}
}
