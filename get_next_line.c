/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:03 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/18 14:57:45 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	set_static_str(char dst[], char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
}







#include<stdio.h>
int		get_next_line(int fd, char **line)
{
	char static	buff[BUFFER_SIZE + 2];
	size_t		bytes_read;
	size_t		tmp;
	size_t		eol;
	size_t		x;

	if(!(*line = malloc(sizeof(char))))
		return (ERR);
	*line = "\0";
	while (buff[0])
	{
		// printf("----------BUFF-----------\n");
		// printf("buff:|%s|\n", buff);
		eol = find_pos_eol(buff);
		// printf("eol :%zu\n", eol);
		*line = ft_strjoin(*line, buff);
		// printf("put in line:|%s|\n", *line);
		tmp = ft_strlen(&buff[eol]);
		// printf("tmp:%zu\n", tmp);
		x = (buff[eol] == '\n');
		// printf("x:%zu\n",x);
		ft_memmove(buff, &buff[eol]+1, tmp + 1);
		buff[tmp] = '\0';
		if (tmp != BUFFER_SIZE)
			ft_bzero(&buff[tmp], eol);
		// printf("put in overflow:|%s|\n", buff);
		if (x)
		{
			// printf("OK1\n");
			return (OK);
		}
	}
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)))
	{
		if (bytes_read < 0)
			return (ERR);
		buff[bytes_read] = '\0';
		// printf("----------READ-----------\n");
		// printf("buff:|%s|\n", buff);
		eol = find_pos_eol(buff);
		// printf("eol :%zu\n", eol);
		*line = ft_strjoin(*line, buff);
		// printf("put in line:|%s|\n", *line);
		tmp = ft_strlen(&buff[eol]);
		// printf("tmp:%zu\n", tmp);
		x = (buff[eol] == '\n');
		ft_memmove(buff, &buff[eol]+1, tmp + 1);
		buff[tmp] = '\0';
		if (tmp != BUFFER_SIZE)
			ft_bzero(&buff[tmp], eol);
		// printf("put in overflow:|%s|\n", buff);
		if (x)
		{
			// printf("OK2\n");
			return (OK);
		}
	}
	return (END);
}







int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;
	int		i;
	int		ret;
	int		nb_line;

	if (argc == 1)
	{
		fd = 0;
		nb_line = 1;
		while((ret = get_next_line(fd, &line)) == 1)
		{
			printf("**********************************************************************************\n");
			printf("LINE NUMBER: %d", nb_line++);
			printf("\nLINE:|%s|\n\n\n", line);
		}
		if (ret == 0)
			printf("\nReached EOF\n");
		else
			printf("\nERROR BITCH\n");
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			printf("Can't open the file\n");
			return (-1);
		}
		nb_line = 1;
		while((ret = get_next_line(fd, &line)) == 1)
		{
			printf("**********************************************************************************\n");
			printf("LINE NUMBER: %d", nb_line++);
			printf("\nLINE:|%s|\n\n\n", line);
		}
		if (ret == 0)
			printf("Reached EOF\n");
		else
			printf("ERROR BITCH\n");
		if (close(fd) == -1)
		{
			printf("Can't close the file\n");
			return (-2);
		}
		if (*line)
			free (line);
		i++;
	}
	return (0);
}
