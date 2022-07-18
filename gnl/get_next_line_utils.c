/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:22:14 by ndillon           #+#    #+#             */
/*   Updated: 2021/12/22 16:22:15 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (NULL);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*start;
	char	*cat_s;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	cat_s = malloc(total_len * sizeof(char));
	if (!cat_s)
		return (NULL);
	start = cat_s;
	while (*s1)
		*(cat_s++) = *(s1++);
	while (*s2)
		*(cat_s++) = *(s2++);
	*cat_s = '\0';
	return (start);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	char	*ptr;

	if (!s1)
		return (NULL);
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
