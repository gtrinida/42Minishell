/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:38:10 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/17 15:41:01 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;

	if (!haystack || !needle)
		return (NULL);
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (*haystack && len)
	{
		i = 0;
		while (*(haystack + i) == needle[i] && len)
		{
			++i;
			--len;
			if (!needle[i])
				return ((char *)haystack);
		}
		len += i - 1;
		++haystack;
	}
	return (NULL);
}
