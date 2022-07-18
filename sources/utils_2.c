/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:28:19 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 01:29:12 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void *data)
{
	if (data)
		free(data);
}

int	safe_close(int fd)
{
	if (fd >= 0)
		return (close(fd));
	return (M_OK);
}

/*
return zero if char is space sym, otherwise return >zero 
*/
int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

void	free_str_arr(char **strings, int n_arg)
{
	int	i;

	i = 0;
	if (strings)
	{
		while (i < n_arg)
			free(strings[i++]);
		free(strings);
	}
}

void	free_strarr_terminated(char **strings)
{
	int	i;

	i = 0;
	if (strings)
	{
		while (strings[i])
			free(strings[i++]);
		free(strings);
	}
}
