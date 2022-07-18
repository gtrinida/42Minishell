/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:36:43 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 13:42:25 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const char *s1, const char *s2, size_t n)
{
	int	res;

	if (!n)
		return (0);
	while (*s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	res = (unsigned char)*s1 - (unsigned char)*s2;
	return (res);
}
