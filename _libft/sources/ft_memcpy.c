/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:00:46 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:01 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*t1;
	char	*t2;

	t1 = (char *)dst;
	t2 = (char *)src;
	while (n-- && (dst || src))
		*t1++ = *t2++;
	return (dst);
}

/*
int main()
{
	printf("%s", ft_memcpy((void *)0, (void *)0, 3));
	printf("%s", memcpy((void *)0, (void *)0, 3));
}*/
