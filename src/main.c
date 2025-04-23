/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:03:47 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/23 16:04:28 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include "mlx.h"
#include "mlx_int.h"
#include <fcntl.h>
	
int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	int		fd;
	char	*line;

	if ((argc - 1) == 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd != -1)
		{
			line = get_next_line(fd);
			while (line)
			{
				printf("%s", line);
				free(line);
				line = get_next_line(fd);
			}
		}
	}
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}
