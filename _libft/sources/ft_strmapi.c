/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:04:11 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:51:02 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*t;

	if (!s)
		return (0);
	t = malloc(ft_strlen((char *)s) + 1);
	if (!t)
		return (0);
	i = -1;
	while (s[++i])
		t[i] = s[i];
	t[i] = 0;
	i = -1;
	while (t[++i])
		t[i] = (*f)(i, t[i]);
	return (t);
}

/*
char	fonction(unsigned int i, char c)
{
	return (c + 1);
}

int main()
{
	printf("%s", ft_strmapi("salut", &fonction));
}*/
