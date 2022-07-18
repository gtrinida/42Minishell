/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:37:34 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:37:34 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	char	*ptr;

	ptr = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	res = ptr;
	while (*s1)
	{
		*ptr = *s1;
		++ptr;
		++s1;
	}
	*ptr = '\0';
	return (res);
}
