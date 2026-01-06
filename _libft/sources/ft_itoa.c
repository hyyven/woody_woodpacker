/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:25:35 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 09:49:31 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_intlen(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	num = (long)n;
	str = malloc(ft_intlen(num) + 1);
	if (!str)
		return (0);
	len = 0;
	if (num < 0)
	{
		num *= -1;
		str[0] = '-';
		len += 1;
	}
	len += ft_intlen(num);
	str[len--] = 0;
	while (num > 9)
	{
		str[len--] = num % 10 + 48;
		num /= 10;
	}
	str[len--] = num + 48;
	return (str);
}
/*
int main()
{
	char *res = ft_itoa(-2147483648LL);
	printf("%s", res);
	free(res);
}*/
