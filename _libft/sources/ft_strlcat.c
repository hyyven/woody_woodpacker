/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:51:55 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:53 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < dstsize && *dst)
		dst++;
	if (i == dstsize)
		return (i + ft_strlen((char *)src));
	j = -1;
	while (src[++j])
		if (j < dstsize - i - 1)
			*dst++ = src[j];
	*dst = 0;
	return (i + j);
}
/*
int main()
{
	char d[15];
	d[0] = 0;
	d[11] = 'a';
	char s[] = "lorem ipsum";
	printf("%zu", ft_strlcat(d, s, 6));
}*/
