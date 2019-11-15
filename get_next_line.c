/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:03 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/15 16:20:17 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_pos_eol(char *str)
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
	char static	overflow[OPEN_MAX][BUFFER_SIZE + 2];
	char		buff[BUFFER_SIZE + 1];
	size_t		bytes_read;
	size_t		cpt;
	size_t		eol;
	size_t		eolovf;
	size_t		smthg;
	size_t		tmp;

	bytes_read = 1;
	cpt = 0;
	if(!(*line = malloc(sizeof(char))))
		return (ERR);
	*line = "\0";
	int i = 12;
	while (i--)
	{
		eolovf = find_pos_eol(overflow[fd]);
		ft_strlcat_malloc(line, overflow[fd], eolovf + 1);
		if (ft_strlen(overflow[fd]) != eolovf)
		{
			set_static_str(overflow[fd], overflow[fd] + eolovf + 1);
			return (OK);
		}
	}
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)))
	{
		//printf("Bytes read:%zu\n", bytes_read);
		if (bytes_read < 0)
			return (ERR);
		buff[bytes_read] = '\0';
		//printf("buff|%s|\n",buff);
		cpt += bytes_read;
		if((eol = find_pos_eol(buff))) //si buff n'est pas vide
		{
			//printf("eol:%zu\n", eol);
			//printf("previous line:|%s|\n", *line);
			if (overflow[fd][0])
			{
				//printf("Previous overflow:|%s|\n", overflow[fd]);
				tmp = find_pos_eol(overflow[fd]);
				ft_strlcat_malloc(line, overflow[fd], tmp + 1);
				//overflow[fd][0] = '\0';
				//printf("line from overflow:|%s|\n", *line);
			}
			if (!ft_strlen(*line) || ft_strlen(*line) != tmp)
				smthg = ft_strlcat_malloc(line, buff, ft_strlen(*line) + eol + 1);/*-+1*/
			//printf("line created:|%s|\n", *line);
			//printf("return strlcat:%zu\n", smthg);
			/*
			if ((smthg % bytes_read))
			{
				set_static_str(overflow[fd], overflow[fd] + find_pos_eol(overflow[fd]) + 1);
				//printf("Overflow from overflow:|%s|\n", overflow[fd]);
				return (OK);
			}
			*/
			if (eol != BUFFER_SIZE && buff[eol + 1])
			{
				set_static_str(overflow[fd], buff + eol + 1);/*+-1*/
				//printf("Overflow from buffer:|%s|\n", overflow[fd]);
				return (OK);
			}
		}
		//printf("OK4\n");
		if (cpt == 0)
		{
			//free(*line);
			return (END);
		}
	}
	//printf("OK\n");
	return (0);//?
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
			printf("*************************************************************\n");
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
			printf("*************************************************************\n");
			printf("LINE NUMBER: %d", nb_line++);
			printf("\nLINE:|%s|\n\n\n", line);
		}
		if (ret == 0)
			printf("\nReached EOF\n");
		else
			printf("\nERROR BITCH\n");
		if (close(fd) == -1)
		{
			printf("Can't close the file\n");
			return (-2);
		}
		i++;
	}
	return (0);
}
