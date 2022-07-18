/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_dollar_env_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 21:39:20 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar_ahead(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	get_finish_utils(char *line, int i, int len)
{
	if (line[i] == '$' && line[i + 1] == '\"')
		return (i - 1);
	if (len - 1 > i)
	{
		if (line[i + 2] && line[i + 1] == '\"')
		{
			if (is_nothing(i + 2) || is_nothing(line[i]))
				return (i - 1);
			return (i);
		}
	}
	if (!line[i + 1] || is_nothing(line[i]))
	{
		if (is_nothing(line[i]))
			return (i - 1);
		if (line[i] == '\"')
			return (i - 1);
		return (i);
	}
	if (line[i] == '\'')
		return (i - 1);
	if (line[i + 1] == '$')
		return (i);
	return (-1);
}

int	get_finish(char *line, int i)
{
	int	len;
	int	end;

	end = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		end = get_finish_utils(line, i, len);
		if (end != -1)
			return (end);
		i++;
	}
	return (-1);
}
