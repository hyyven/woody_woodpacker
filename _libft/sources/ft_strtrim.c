/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:17:18 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:51:11 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	size_trim(char const *s1, char const *set)
{
	int	size;
	int	i;

	size = ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		size--;
	}
	i = ft_strlen(s1) - 1;
	while (i && ft_strchr(set, s1[i]))
	{
		i--;
		size--;
	}
	if (size < 0)
		return (0);
	return (size);
}

static char	*trim_vide(char const *s1)
{
	char	*t;
	int		i;

	t = malloc(ft_strlen(s1) + 1);
	i = 0;
	while (*s1)
		t[i++] = *s1++;
	t[i] = 0;
	return (t);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*t;

	if (!s1)
		return (0);
	if (!set[0] || !s1[0])
		return (trim_vide(s1));
	t = malloc(size_trim(s1, set) + 1);
	if (!t)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	i++;
	j = 0;
	while (*s1 && i--)
		t[j++] = *s1++;
	t[j] = 0;
	return (t);
}

/*
int main()
{
	printf("%s", ft_strtrim("", ""));
}*/
