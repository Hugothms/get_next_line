/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:01 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/25 17:19:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# define END_OF_LINE '\n'
# define ERR -1
# define END 0
# define OK 1

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

size_t			ft_strlen(const char *str);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_bzero(void *b, size_t len);
size_t			find_pos_eol(const char *line);
int				fill_line_with_buff(char **line, char buff[BUFFER_SIZE + 1], size_t start);
int				get_next_line(int fd, char **line);

#endif
