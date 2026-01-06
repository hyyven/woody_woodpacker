/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:44:07 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:41 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c %= 128;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (&(((char *)s)[i]));
	return (NULL);
}
/*
int main()
{
	printf("%s\n", ft_strchr("salut ca va", 't' + 256));
	printf("%s", strchr("salut ca va ", 't' + 256));
}*/
