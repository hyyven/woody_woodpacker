/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:41:09 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:51:14 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	int		i;
	int		l;

	i = 0;
	l = (int)len;
	if (!s)
		return (0);
	if (l >= 0 && ft_strlen((char *)s) > len)
		t = malloc(l + 1);
	else
		t = malloc(ft_strlen((char *)s) + 1);
	if (!t)
		return (0);
	t[0] = 0;
	if (ft_strlen((char *)s) < start)
		return (t);
	while (s[start] && len--)
		t[i++] = s[start++];
	t[i] = 0;
	return (t);
}

/*
int	main()
{
	printf("%s", ft_substr("", 1, 1));
}*/
