/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:03 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/14 19:40:22 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



void	ft_putstr(const char* str)
{
	int	i;

	i = 0;
	while(str[i])
		write(1, str + i++, 1);
}













size_t	end_of_line_reached(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != END_OF_LINE)
		i++;
	if (str[i] == END_OF_LINE)
		return (i);
	return (-1);
}

void	set_static_str(char dst[], char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
	}
	dst[i] = src[i];
}

int		get_next_line(int fd, char **line)
{
	char static	overflow[OPEN_MAX][BUFFER_SIZE + 2];
	char		buff[BUFFER_SIZE + 1];
	size_t		bytes_read;
	size_t		cpt;
	size_t		eol;
	size_t		qqpart;

	bytes_read = 1;
	cpt = 0;
	if(!(*line = malloc(sizeof(char))))
		return (ERR);
	*line = "\0";
	while (bytes_read)
	{
		ft_putstr("OK1\n");
		bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = '\0';
		if (bytes_read < 0)
			return (ERR);
		cpt += bytes_read;
		//printf("%s",buff);
		ft_putstr("OK2\n");
		if((eol = end_of_line_reached(buff)) && (int)eol != -1)
		{
			if (overflow[fd][0])
				ft_strlcat_malloc(*line, overflow[fd], ft_strlen(overflow[fd]));
			qqpart = ft_strlcat_malloc(*line, buff, eol);/*-+1*/
			ft_putstr(*line);
			ft_putstr("OK3\n");
			set_static_str(overflow[fd], buff + eol + 1);/*+-1*/
			return (1);
		}
	}
	ft_putstr("OK4\n");
	if (cpt == 0)
	{
		free(*line);
		return (0);
	}
	ft_putstr("OK\n");
	return (1);//?
}







int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;
	int		i;
	int		ret;
	int		nb_line;
	char	c;

	if (argc == 1)
	{
		fd = 0;
		nb_line = 0;
		while((ret = get_next_line(fd, &line)) == 1)
		{
			ft_putstr("Line number:");
			c = '0' + nb_line++;
			write(1, &c, 1);
			ft_putstr("\n");
			ft_putstr(line);
			ft_putstr("\n");
		}
		if (ret == 0)
			ft_putstr("\nReached EOF\n");
		else
			ft_putstr("\nERROR BITCH\n");
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (-1);
		nb_line = 0;
		while((ret = get_next_line(fd, &line)) == 1)
		{
			ft_putstr("Line number:");
			c = '0' + nb_line++;
			write(1, &c, 1);
			ft_putstr("\n");
			ft_putstr(line);
			ft_putstr("\n");
		}
		if (ret == 0)
			ft_putstr("\nReached EOF\n");
		else
			ft_putstr("\nERROR BITCH\n");
		if (close(fd) == -1)
			return (-2);
		i++;
	}
	return (0);
}
