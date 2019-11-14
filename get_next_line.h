/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:01 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/14 19:33:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif
# define END_OF_LINE '\n'
# define ERR -1


# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

size_t			end_of_line_reached(char *line);
size_t			ft_strlen(const char *str);
size_t			ft_strnlen(const char *str, size_t sizemax);
void			*ft_memcpy(void *dst, const void *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat_malloc(char *dst, char *src, size_t maxlen);
int				get_next_line(int fd, char **line);

#endif
