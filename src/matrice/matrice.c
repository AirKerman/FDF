/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:56:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:40:01 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_y(int **tab, int size_tab)
{
	int		i;
	float	x;
	float	z;

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

void	rotate_z(int **tab, int size_tab)
{
	int		i;
	float	x;
	float	z;

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

void	rotate_x(int **tab, int size_tab)
{
	int		i;
	float	x;
	float	z;

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
