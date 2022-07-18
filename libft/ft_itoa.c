/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:33:19 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:33:22 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_reverse(char *str)
{
	int		start;
	int		len;
	char	temp;

	if (!str)
		return (NULL);
	start = 0;
	len = ft_strlen(str) - 1;
	while (start < len / 2 + 1)
	{
		temp = str[start];
		str[start] = str[len - start];
		str[len - start] = temp;
		++start;
	}
	return (str);
}

static int	ft_intlen(long long n, int sign)
{
	int	len;

	len = 1;
	if (!n)
		return (len + 1);
	if (sign)
		len++;
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			sign;
	long long	x;

	x = n;
	sign = (x < 0 && x);
	if (sign)
		x = -x;
	str = malloc(ft_intlen(x, sign) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (!x)
		str[i++] = '0';
	while (x)
	{
		str[i++] = x % 10 + '0';
		x /= 10;
	}
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_reverse(str));
}
