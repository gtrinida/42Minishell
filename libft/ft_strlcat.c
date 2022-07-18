/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:37:48 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/17 15:19:51 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;
	char	*ptr;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if ((int)dstsize - (int)dst_len < 1 && (int)dstsize >= 0)
		return (dstsize + src_len);
	total_len = dst_len + src_len;
	ptr = dst;
	while (dst_len < dstsize - 1 && *src)
	{
		ptr[dst_len] = *(src++);
		++dst_len;
	}
	ptr[dst_len] = '\0';
	return (total_len);
}
