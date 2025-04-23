/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:53:06 by rkerman           #+#    #+#             */
/*   Updated: 2025/04/23 16:04:45 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*ft_read(char *s, int fd)
{
	char	*b;
	int		j;
	int		i;

	b = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (b == NULL)
		return (NULL);
	j = 1;
	i = 0;
	while (!ft_chr_c(s, '\n') && j != 0)
	{
		j = read(fd, b, BUFFER_SIZE);
		if (j == -1 || (j == 0 && i == 0 && s == NULL))
		{
			free (b);
			if (s)
				free (s);
			return (NULL);
		}
		b[j] = '\0';
		s = ft_strjoin(s, b);
		i++;
	}
	free (b);
	return (s);
}

static int	ft_free_stash(char *s, char *str, int i)
{
	if (str == NULL || !s[i + 1])
	{
		if (!s[i + 1])
			free(str);
		free(s);
		return (1);
	}
	return (0);
}

static char	*ft_newstash(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free (s);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(s) - i), sizeof(char));
	if (ft_free_stash(s, str, i))
		return (NULL);
	i++;
	j = 0;
	while (s[i] != '\0')
		str[j++] = s[i++];
	free (s);
	return (str);
}

static char	*ft_newline(char *s)
{
	int		i;
	char	*new;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	new = (char *)malloc((i + 2) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		new[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[4096];

	stash[fd] = ft_read(stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	line = ft_newline(stash[fd]);
	stash[fd] = ft_newstash(stash[fd]);
	return (line);
}
