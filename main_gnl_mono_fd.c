/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_no_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:52:49 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/27 13:15:46 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
//#include "get_next_line.h"
//#include "iterative_
//#include "tsansbonus.h"
//int        main(void)
int        main(int argc, char **argv)
{
    int        fd;
    char    *line;
    int        i;
    int ret;

    i = 0;
    //fd = 0;
    if (argc == 2)
        fd = open((argv[1]), O_RDONLY);
    else
        fd = 0;
    while ((ret = get_next_line(fd, &line)) == 1)
    {
        printf("\nret: %d line = |%s|\n", ret, line);
        free(line);
    }
    if (ret == 0)
    {
        printf("\nret: %d line = |%s|\n", ret, line);
        free(line);
    }
	else if (ret == -1)
    {
		printf("\nret: %d line = |%s|\n", ret, line);
        free(line);
    }
      // system("leaks a.out");
    close(fd);
    return (0);
}