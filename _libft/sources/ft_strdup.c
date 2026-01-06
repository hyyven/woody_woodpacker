/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:44:39 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:44 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *) malloc(ft_strlen((char *)s1) + 1 * sizeof(char));
	if (!copy)
		return (0);
	while (*s1)
		copy[i++] = *s1++;
	copy[i] = 0;
	return (copy);
}

/*
int main()
{
	char str[] = "salut ca va";
	printf("%s\n", ft_strdup(str));
	printf("%s", strdup(str));
}*/
