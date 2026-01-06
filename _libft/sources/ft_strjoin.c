/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:05:47 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:50 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*t;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	t = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!t)
		return (0);
	while (*s1)
		t[i++] = *s1++;
	while (*s2)
		t[i++] = *s2++;
	t[i] = 0;
	return (t);
}

/*
int main()
{
	char s1[] = "salut ";
	char s2[] = "	";
	printf("%s", ft_strjoin(s1, s2));
}*/
