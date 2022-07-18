/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:38:01 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:38:01 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*strmap;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	strmap = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!strmap)
		return (NULL);
	while (*s)
	{
		*(strmap + i) = f(i, *s);
		i++;
		s++;
	}
	*(strmap + i) = '\0';
	return (strmap);
}
