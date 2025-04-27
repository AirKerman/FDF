/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:04:02 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/27 15:09:01 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FDF
#define	FDF

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

#include "mlx.h"
#include "mlx_int.h"
#include <stdint.h>
#include <fcntl.h>

typedef struct t_value
{
	int	size;
	int	width;
	int	height;
}	t_val;


char	*get_next_line(int fd);
int		ft_chr_c(char *s, int c);
char	*ft_strjoin(char *s, char *b);
int		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);


#endif
