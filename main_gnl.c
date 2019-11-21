/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:52:49 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/21 14:55:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int		fd[argc];
	char	*line[2];
	int		i;
	int		ret[argc];
	int		nb_line;

	if (argc == 1)
	{
		fd[0] = 0;
		nb_line = 1;
		while ((ret[0] = get_next_line(fd[0], line)) == 1)
		{
			printf("*************************************\n");
			printf("LINE NUMBER: %d", nb_line++);
			printf("\n|%s|\n\n\n", *line);
		}
		if (ret[0] == 0)
			printf("\nReached EOF\n");
		else
			printf("\nERROR BITCH\n");
	}
	i = 1;
	///////////////////////////////////////////////////////////////////////////
	while (i < argc)
	{
		fd[i] = open(argv[i], O_RDONLY);
		if (fd[i] == -1)
		{
			printf("Can't open the file:%s\n", argv[i]);
			return (-1);
		}
		i++;
	}
	nb_line = 1;
	i = 1;
	line[0] = malloc(1);
	line[1] = malloc(1);
	while ((ret[0] = get_next_line(fd[1], &line[0])) && (ret[1] = get_next_line(fd[2], &line[1])))
	{
		printf("|%s|\n", line[0]);
		printf("|%s|\n\n", line[1]);
		nb_line++;
		i++;
	}
	if (ret[0] == 0)
		printf("Reached EOF:%s\n", argv[1]);
	if (ret[1] == 0)
		printf("Reached EOF:%s\n", argv[2]);
	while ((ret[0] = get_next_line(fd[1], &line[0])))
	{
		printf("|%s|\n", line[0]);
		i++;
		nb_line++;
	}
	while ((ret[1] = get_next_line(fd[2], &line[1])))
	{
		printf("|%s|\n\n", line[1]);
		nb_line++;
		i++;
	}
	if (ret[0] == 0)
		printf("Reached EOF:%s\n", argv[1]);
	else if (ret[1] == 0)
		printf("Reached EOF:%s\n", argv[2]);
	else
		printf("ERROR BITCH\n");
	i = 1;
	while (i < argc)
	{
		if (close(fd[i]) == -1)
		{
			printf("Can't close the file\n");
			return (-2);
		}
		if (*line[i - 1])
			free(line[i - 1]);
		i++;
	}
	return (0);
}
