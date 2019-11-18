/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:52:49 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/18 15:53:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
