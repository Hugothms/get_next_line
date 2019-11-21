/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:39 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/21 17:16:32 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_pos_eol(const char *str)
{
	size_t	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != END_OF_LINE)
		i++;
	return (i);
}

int		fill_line_with_buff(char **line, char buff[][BUFFER_SIZE + 2], int fd)
{
	size_t		tmp;
	size_t		eol;

	if (!*buff[fd] && **line)
		return (OK);
	if (*buff[fd] == END_OF_LINE && !buff[fd][1])
	{
		ft_memmove(buff[fd], &buff[fd][1], 1);
		return (OK);
	}
	eol = find_pos_eol(buff[fd]);
	tmp = ft_strlen(&buff[fd][eol]);
	*line = ft_strjoin(*line, &buff[fd][(buff[fd][0] == END_OF_LINE)]);
	if (*buff[fd] == END_OF_LINE)
		**line = '\0';
	ft_memmove(buff[fd], &buff[fd][eol] + 1, tmp + 1);
	buff[fd][tmp] = '\0';
	if (tmp != BUFFER_SIZE)
		ft_bzero(&buff[fd][tmp], eol);
	if (tmp)
		return (OK);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 2];
	size_t		bytes_read;

	if (BUFFER_SIZE == 0 || fd < 0 || line == NULL)
		return (ERR);
	if (!(*line = malloc(sizeof(char))))
		return (ERR);
	*line = "\0";
	while (*buff[fd])
	{
		if (fill_line_with_buff(line, buff, fd))
			return (OK);
	}
	while ((bytes_read = read(fd, buff[fd], BUFFER_SIZE)))
	{
		if (bytes_read < 0)
			return (ERR);
		buff[fd][bytes_read] = '\0';
		if (fill_line_with_buff(line, buff, fd))
			return (OK);
	}
	return (END);
}
