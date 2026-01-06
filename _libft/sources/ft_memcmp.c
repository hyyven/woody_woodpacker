/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:11:00 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:49:59 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*t1;
	char	*t2;

	t1 = (char *)s1;
	t2 = (char *)s2;
	while (n--)
	{
		if (*t1 != *t2)
			return ((unsigned char)*t1 - (unsigned char)*t2);
		t1++;
		t2++;
	}
	return (0);
}
/*
int main()
{
	char s1[50] = "salut";
	char s2[50] = "salut";
	printf("%d", ft_memcmp(s1, s2, 6));
	printf("%d", memcmp(s1, s2, 6));
}*/
