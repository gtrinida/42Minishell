/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:38:22 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:38:22 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in(char c, char const *set)
{
	int	flag;

	flag = 0;
	while (*set)
	{
		if (c == *(set++))
		{
			flag = 1;
			break ;
		}
	}
	return (flag);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start])
		if (!ft_in(s1[start++], set))
			break ;
	if (ft_in(s1[--start], set))
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end >= 0 && s1[end])
		if (!ft_in(s1[end--], set))
			break ;
	trimmed = (char *)malloc((end - start + 3) * sizeof(char));
	if (!trimmed)
		return (NULL);
	res = trimmed;
	while (start >= 0 && start <= end + 1)
		*(trimmed++) = s1[start++];
	*trimmed = '\0';
	return (res);
}
