/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:39 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/18 16:05:05 by hthomas          ###   ########.fr       */
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
	if (str[i] == END_OF_LINE)
		return (i);
	return (i);
}

int		just_do_it(char **line, char *buff)
{
	size_t		tmp;
	size_t		eol;
	size_t		x;

	eol = find_pos_eol(buff);
	*line = ft_strjoin(*line, buff);
	tmp = ft_strlen(&buff[eol]);
	x = (buff[eol] == '\n');
	ft_memmove(buff, &buff[eol] + 1, tmp + 1);
	buff[tmp] = '\0';
	if (tmp != BUFFER_SIZE)
		ft_bzero(&buff[tmp], eol);
	return (x);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 2];
	size_t		bytes_read;

	if (!(*line = malloc(sizeof(char))))
		return (ERR);
	*line = "\0";
	while (buff[0])
	{
		if (just_do_it(line, buff))
			return (OK);
	}
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)))
	{
		if (bytes_read < 0)
			return (ERR);
		buff[bytes_read] = '\0';
		if (just_do_it(line, buff))
			return (OK);
	}
	return (END);
}
