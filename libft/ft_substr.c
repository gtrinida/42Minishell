/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:38:26 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:38:26 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	while (s[start + i] && i < len)
		i++;
	sub_s = (char *)malloc((i + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	j = 0;
	i += start;
	while (start < i)
		sub_s[j++] = s[start++];
	sub_s[j] = '\0';
	return (sub_s);
}
