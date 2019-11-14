/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:29:03 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/14 11:41:08 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_stdin(void)
{
	char	buff[BF_SIZE + 1];
	char	*str;
	int		ret;

	if (!(str = malloc(sizeof(char) * 1)))
		return (0);
	str[0] = '\0';
	while ((ret = read(STDIN_FILENO, buff, BF_SIZE)))
	{
		buff[ret] = '\0';
		str = ft_strcat_malloc(str, buff);
	}
	return (str);
}

int		end_of_line_reached(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (i);
	else
		return (-1);
}

int		get_next_line(int fd, char **line)
{
	char static	*next_line;
	char		buff[BF_SIZE];
	int			bytes_read;
	int			cpt;
	int			eol;

	bytes_read = 1;
	cpt = 0;
	while (bytes_read)
	{
		bytes_read = read(fd, buff, BF_SIZE);
		if (bytes_read < 0)
			return (-1);
		cpt += bytes_read;
		if(!(eol = end_of_line_reached(line)))
		{
			ft_strlcat_malloc(line, buff, eol);
			next_line = buff + eol;
			break;
		}
	}
	if (cpt == 0)
		return (0);
	return (1);
}













static size_t	ft_strnlen(const char *str, size_t sizemax)
{
	size_t	i;

	i = 0;
	while (str[i] && i < sizemax)
		i++;
	return (i);
}
static size_t	ft_strnlen(const char *str, size_t sizemax)
{
	size_t	i;

	i = 0;
	while (str[i] && i < sizemax)
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lensrc;
	size_t	lendst;

	lensrc = ft_strlen(src);
	lendst = ft_strnlen(dst, dstsize);
	if (lendst == dstsize)
		return (lensrc + dstsize);
	if (lensrc < dstsize - lendst)
		ft_memcpy(dst + lendst, src, lensrc + 1);
	else
	{
		ft_memcpy(dst + lendst, src, dstsize - lendst - 1);
		dst[lendst + dstsize - lendst - 1] = '\0';
	}
	return (lensrc + lendst);
}

char		*ft_strcat_malloc(char *src, char *buffer)
{
	char	*dest;

	dest = malloc((ft_strlen(src) + ft_strlen(buffer) + 1) * sizeof(char));
	dest[0] = '\0';
	ft_strcat(dest, src);
	ft_strcat(dest, buffer);
	free(src);
	src = dest;
	return (src);
}




































void	ft_putstr(const char* str)
{
	int	i;

	i = 0;
	while(str[i])
		write(1, str[i++], 1);
}

int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;
	int		i;
	int		ret;
	int		nb_line;

	if (argv != 2)
		return (0);

	if (!ft_strcmp(argv[1], "stdin"))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (-1);
	}
	else
		fd = 0;

	nb_line = 0;
	while((ret = get_next_line(fd, &line)) == 1)
	{
		ft_putstr("Line number:");
		write(1, '0' + nb_line++,1);
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
	return (0);
}
