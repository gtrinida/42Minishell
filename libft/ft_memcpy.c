/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:36:49 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:36:49 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp;

	if (dst && src && n)
	{
		temp = dst;
		while (n)
		{
			n--;
			temp[n] = ((const char *)src)[n];
		}
	}
	return (dst);
}
