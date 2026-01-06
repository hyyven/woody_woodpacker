/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:01:09 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:49:15 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*t;

	t = malloc(count * size);
	if (!t)
		return (0);
	ft_bzero(t, count * size);
	return (t);
}

/*
int main()
{
	char *p = ft_calloc(10, sizeof(long));
	int i = 0;
	while (i++ < 24)
		printf("%c", p[i]);	
	printf("\n");

	char *k = calloc(10, sizeof(long));
	int j = 0;
	while (j++ < 24)
		printf("%c", k[j]);
}*/	
