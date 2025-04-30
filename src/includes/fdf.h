/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:04:02 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/30 12:55:44 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef COLOR
#  define COLOR 0xFFFFFF
# endif
# ifndef MULTI
#  define MULTI 100
# endif
# ifndef Z_MULTI
#  define Z_MULTI 40
# endif
# ifndef ROTATESPEED
#  define ROTATESPEED 0.05f
# endif
# ifndef SIZE_W
#  define SIZE_W 1920
# endif
# ifndef SIZE_H
#  define SIZE_H 1080
# endif

# include "mlx.h"
# include "mlx_int.h"
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

typedef struct t_value
{
	int		**grid;
	void	*img;
	char	*addr;
	int		lw;
	int		bpp;
	int		endian;
	int		width;
	int		height;
	int		size;
	int		w_lag;
	int		h_lag;
	int		multi;
	void	*mlx;
	void	*mlx_win;
}	t_val;

typedef struct t_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
}	t_bre;

typedef struct t_filling
{
	int		fd;
	char	**s;
	char	*l;
	int		x;
	int		y;
	int		i;
}	t_fill;

char	*get_next_line(int fd);
int		ft_chr_c(char *s, int c);
char	*ft_strjoin(char *s, char *b);
int		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(char const *s, char c);
int		countwords(char *str);
int		ft_atoi(char *s);
int		c_sch(char *s, char c);
int		is_hex(char *s);
int		ft_hextoi(char *s, int len);
void	rotate_y(int **tab, int size_tab);
void	rotate_z(int **tab, int size_tab);
void	rotate_x(int **tab, int size_tab);
void	r_rotate_x(int **tab, int size_tab);
void	r_rotate_y(int **tab, int size_tab);
void	r_rotate_z(int **tab, int size_tab);
void	put_p(t_val *data, int x, int y, int c);
void	free_all(int **g);
int		ft_abs(int n);
void	mult_tab(t_val *d);
void	center_grid(t_val *d);
int		grid_fill(char *path, t_val *data);
int		file_checker(char *path, t_val *data);
int		file_processing(char *path, t_val *data);
int		handler_hook(int keycode, t_val *d);
void	init_data(t_val *data);
void	bresenham(t_val *d, int *p1, int *p2);
void	init_data(t_val *data);
int		close_win(t_val *d);

#endif
