/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:28:57 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/15 13:03:49 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

size_t			ft_strlcat_malloc(char **dst, char *src, size_t maxlen)
{
	char	*new;
	size_t	length;
	size_t	dstlen;

	dstlen = 0;
	//if (*dst)
		dstlen = ft_strlen(*dst);
	new = malloc((dstlen + ft_strnlen(src, maxlen) + 1) * sizeof(char));
	new[0] = '\0';
	ft_strlcat(new, *dst, dstlen + 1);
	//free(*dst);
	length = ft_strlcat(new, src, maxlen);
	*dst = new;
	return (length);
}
