/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:39 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/25 18:12:12 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_pos_eol(const char *str)
{
	size_t	i;

	i = 0;
	if (!str[i])
		return (0);
	/*if (str[i] == END_OF_LINE)
		i++;*/
	while (str[i] && str[i] != END_OF_LINE)
		i++;
	return (i);
}
#include<stdio.h>
/*
int		fill_line_with_buff(char **line, char buff[][BUFFER_SIZE + 1], int fd)
{
	size_t		tmp;
	size_t		eol;

	// printf("*******************************buffbefore|%s|\n",buff[fd]);
	if (!*buff[fd] && **line)
		return (OK);
	if (*buff[fd] == END_OF_LINE && !buff[fd][1])
	{
		ft_memmove(buff[fd], &buff[fd][1], 1);
		// printf("*******************************buffhidden|%s|\n",buff[fd]);
		(void)buff[fd];
		return (OK);
	}
	eol = find_pos_eol(buff[fd]);			//cb on met dans line
	*line = ft_strjoin(*line, buff[fd]);
	if (**line == END_OF_LINE)
		**line = '\0';
	tmp = ft_strlen(&buff[fd][eol]);		//cb il reste dans le buff
	ft_memmove(buff[fd], &buff[fd][eol], tmp + 1);
	buff[fd][tmp] = '\0';
	if (tmp != BUFFER_SIZE)
		ft_bzero(&buff[fd][tmp], eol);
	// printf("*******************************line|%s|\n",*line);
	// printf("*******************************buffafter|%s|\n",buff[fd]);
	// printf("*******************************eol|%zu|\n",eol);
	// printf("*******************************tmp|%zu|\n",tmp);
	if (tmp)
		return (OK);
	return (0);
}
*/

int		fill_line_with_buff(char **line, char buff[BUFFER_SIZE + 1], size_t start)
{
	size_t		rest_buff;
	size_t		eol;

	// printf("*******************************buffbefore|%s|\n",buff);
	// printf("*******************************buffbeforestart|%s|\n",&buff[start]);
	if (!*buff && **line)
	{
		ft_memmove(buff, &buff[1], 1);
		return (OK);
	}
	if (*buff == END_OF_LINE && !buff[1])
	{
		ft_memmove(buff, &buff[1], 1);
		return (OK);
	}
	eol = find_pos_eol(&buff[start]);
	rest_buff = ft_strlen(&buff[eol]);
	*line = ft_strjoin(*line, &buff[start]);
	if (buff[start] == END_OF_LINE)
		**line = '\0';
	ft_memmove(buff, &buff[start + eol], start + rest_buff);
	buff[rest_buff] = '\0';
	if (rest_buff != BUFFER_SIZE)
		ft_bzero(&buff[rest_buff], eol);
	// printf("*******************************line|%s|\n",*line);
	// printf("*******************************buffafter|%s|\n",buff);
	// printf("*******************************eol|%zu|\n",eol);
	// printf("*******************************rest_buff|%zu|\n",rest_buff);
	if (rest_buff)
		return (OK);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	size_t		bytes_read;

	if (BUFFER_SIZE == 0 || fd < 0 || line == NULL)
		return (ERR);
	if (!(*line = malloc(sizeof(char))))
		return (ERR);
	*line = "\0";
	while (*buff[fd])
	{
		// printf("BUFF\n");
		if (fill_line_with_buff(line, buff[fd], 1))
			return (OK);
	}
	while ((bytes_read = read(fd, buff[fd], BUFFER_SIZE)) || *buff[fd])
	{
		// printf("READ\n");
		if (bytes_read < 0)
			return (ERR);
		buff[fd][bytes_read] = '\0';
		if (fill_line_with_buff(line, buff[fd], 0))
			return (OK);
	}
	if (fill_line_with_buff(line, buff[fd], 1))
		return (OK);
	return (END);
}
