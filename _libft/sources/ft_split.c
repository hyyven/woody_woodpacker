/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:00:34 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:50:37 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count(char *str, char c)
{
	int	cmp;

	cmp = 0;
	if (!c && !str[0])
		return (0);
	while (*str == c)
		str++;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			cmp++;
			while (*str && *str != c)
				str++;
		}
	}
	return (cmp);
}

static char	*ft_strncpy(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(len + 1);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static int	ft_strlen2(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		lentab;
	int		i;
	int		j;

	if (!s)
		return (0);
	j = 0;
	i = 0;
	lentab = ft_count((char *)s, c) + 1;
	tab = malloc(lentab * sizeof(char *));
	if (!tab)
		return (0);
	while (--lentab)
	{
		while (s[j] == c)
			j++;
		tab[i++] = ft_strncpy((char *)&s[j], ft_strlen2((char *)&s[j], c));
		j += ft_strlen2((char *)&s[j], c);
	}
	tab[i] = 0;
	return (tab);
}

/*
int main()
{
	char **tab = ft_split("\0aa\0bbb", '\0');
}*/
