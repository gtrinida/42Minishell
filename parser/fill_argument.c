/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 04:39:44 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	somethind_ahead(char *line, int i)
{
	if (is_nothing(line[i]))
		return (1);
	i++;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (!is_nothing(line[i]) && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

void	pass_params(t_params *data, t_quotes *quot, int i)
{
	quot->end = i;
	data->node->need_to_assign = 1;
}

int	find_arguments_utils(t_params *data, t_quotes *quot, int i, int flag)
{
	while (data->line[i])
	{
		if ((data->line[quot->start] == '>'
				|| data->line[quot->start] == '<') && !flag)
		{
			pass_params(data, quot, i);
			return (0);
		}
		if ((data->line[i] == '>' || data->line[i] == '<') && !flag)
		{
			pass_params(data, quot, i);
			return (1);
		}
		if (data->line[i] == '\r' && flag)
			flag = 0;
		else if (data->line[i] == '\r' && !flag && check_ahead(data->line, i))
			flag = 1;
		if ((is_nothing(data->line[i]) || data->line[i + 1] == '\0') && !flag)
		{
			quot->end = i;
			return (1);
		}
		i++;
	}
	return (1);
}

int	find_arguments(t_params *data, t_quotes *quot)
{
	int	i;
	int	flag;

	flag = 0;
	i = quot->start;
	while (is_nothing(data->line[i]))
		i++;
	if (data->line[i])
	{
		quot->start = i;
		return (find_arguments_utils(data, quot, i, flag));
	}
	return (1);
}

void	fill_argument(t_params *data, t_quotes *quot)
{
	int	i;
	int	end;

	end = quot->end;
	i = 0;
	if (data->node->need_to_assign || somethind_ahead(data->line, end))
		end--;
	data->node->arg[quot->i_arg] = malloc(end - quot->start + 2);
	while (quot->start <= end)
	{
		if (data->line[quot->start] != '\r')
		{
			if (data->line[quot->start] == '\a')
				data->line[quot->start] = '?';
			data->node->arg[quot->i_arg][i] = data->line[quot->start];
			i++;
		}
		quot->start++;
	}
	data->node->arg[quot->i_arg][i] = '\0';
}
