/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:04:02 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/24 15:03:06 by rkerman          ###   ########.fr       */
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

char	*get_next_line(int fd);
int	ft_chr_c(char *s, int c);
char	*ft_strjoin(char *s, char *b);
int		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);


#endif
