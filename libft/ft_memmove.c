/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:36:53 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 12:41:43 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		direction;
	char	*d;
	char	*s;

	if (!dst || !src)
		return (NULL);
	d = dst;
	s = (char *)src;
	direction = 1;
	if (dst > src)
	{
		direction = -1;
		d += len - 1;
		s += len - 1;
	}
	while (len--)
	{
		*d = *s;
		d += 1 * direction;
		s += 1 * direction;
	}
	return (dst);
}
