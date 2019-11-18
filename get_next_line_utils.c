/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:28:57 by hthomas           #+#    #+#             */
/*   Updated: 2019/11/18 16:04:59 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
