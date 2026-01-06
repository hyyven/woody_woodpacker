/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:23:56 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:04 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*t1;
	char	*t2;

	t1 = (char *)dst;
	t2 = (char *)src;
	if (!dst && !src)
		return (0);
	if (t1 > t2)
		while (len--)
			t1[len] = t2[len];
	else
		while (len--)
			*t1++ = *t2++;
	return (dst);
}

/*
int main()
{
	printf("%s\n", ft_memmove(((void *)0), ((void *)0), 5));
	printf("%s", memmove(((void *)0), ((void *)0), 5));
}*/
