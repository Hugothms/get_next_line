/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:28:57 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/18 14:32:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//////////////////////////////////1
size_t			ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t			ft_strnlen(const char *str, size_t sizemax)
{
	size_t	i;

	i = 0;
	while (str[i] && i < sizemax)
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
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

size_t			ft_strlcat_malloc(char **line, char *src, size_t maxlen)
{
	char	*new;
	size_t	length;
	size_t	linelen;

	linelen = 0;
	//if (*line)
		linelen = ft_strlen(*line);
	new = malloc((linelen + ft_strnlen(src, maxlen) + 1) * sizeof(char));
	new[0] = '\0';
	ft_strlcat(new, *line, linelen + 1);
	if(**line)
		free(*line);
	length = ft_strlcat(new, src, maxlen);
	*line = new;
	return (length);
}





//////////////////////////////2
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst1;
	char		*lastd;
	const char	*src1;
	const char	*lasts;

	if (!dst && !src)
		return (dst);
	dst1 = (char *)dst;
	src1 = (char *)src;
	if (dst1 < src1)
	{
		while (len--)
			*dst1++ = *src1++;
	}
	else
	{
		lasts = src1 + (len - 1);
		lastd = dst1 + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}

size_t	find_pos_eol(const char *str)
{
	size_t	i;

	i = 0;
	if (!str[i])
		return (0);
	// if (str[i] == '\n')
	// 	i++;
	while (str[i] && str[i] != END_OF_LINE)
		i++;
	if (str[i] == END_OF_LINE)
		return (i);
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = find_pos_eol(s2);
	if (!(new = malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
	ft_memmove(new, s1, lens1);
	ft_memmove(new + lens1, s2, lens2);
	new[lens1 + lens2] = '\0';
	return (new);
}

void	*ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
		str[i++] = '\0';
	return (b);
}
