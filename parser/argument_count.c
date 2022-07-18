/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/21 23:22:38 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argument_count_utils(t_params *data, int flag, int *count, int *i)
{
	if ((is_nothing(data->line[*i]) || data->line[*i + 1] == '\0')
		&& !flag)
	{	
		(*count)++;
		while (is_nothing(data->line[*i + 1]))
			(*i)++;
		if (!data->line[*i])
			return (0);
	}
	return (1);
}

int	argument_count(t_params *data, t_quotes *quot, int count, int flag)
{
	int	i;

	i = quot->start;
	while (is_nothing(data->line[i]))
		i++;
	while (data->line[i])
	{
		if ((data->line[i] == '>' || data->line[i] == '<') && !flag)
		{
			correct_count(data, &i);
			if (data->line[i + 1] == '>' || data->line[i + 1] == '<')
				i++;
		}
		if (data->line[i] == '\r' && flag)
			flag = 0;
		else if (data->line[i] == '\r' && !flag && check_ahead(data->line, i))
			flag = 1;
		if (!argument_count_utils(data, flag, &count, &i))
			return (count);
		i++;
	}
	return (count);
}
