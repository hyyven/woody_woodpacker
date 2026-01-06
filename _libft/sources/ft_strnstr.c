/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:29:42 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:51:06 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *hay, const char *n, size_t len)
{
	size_t	len_n;

	if (!len && (!hay || !n))
		return (0);
	len_n = ft_strlen((char *)n);
	if (!len_n)
		return ((char *)hay);
	hay--;
	len++;
	while (*++hay && --len)
		if (n[0] == hay[0] && len >= len_n && !ft_strncmp(hay, n, len_n))
			return ((char *)hay);
	return (0);
}

/*
int main()
{
	char hay[] = "aaabc";
	char needle[] = "aaabc";
	printf("%s\n", ft_strnstr(hay, needle, 5));
	char h[] = "aaabc";
    char n[] = "aaabc";
	printf("%s", strnstr(h, n, 5));
}*/
