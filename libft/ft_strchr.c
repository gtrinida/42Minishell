/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:37:28 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/16 14:00:46 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	c = (unsigned char)c;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	ptr = NULL;
	while (*s)
	{
		if (*s == c)
		{
			ptr = (char *)s;
			break ;
		}
		s++;
	}
	return (ptr);
}
