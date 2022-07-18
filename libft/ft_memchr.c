/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:36:38 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/17 15:37:52 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;

	c = (unsigned char)c;
	ptr = NULL;
	while (n)
	{
		if (*((unsigned char *) s) == c)
		{
			ptr = (char *)s;
			break ;
		}
		s++;
		--n;
	}
	return (ptr);
}
