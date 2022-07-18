/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 22:44:14 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ahead(char *line, int i)
{
	if (line[i + 1] == '\0')
		return (0);
	i++;
	while (line[i])
	{
		if (line[i] == '\r')
			return (1);
		i++;
	}
	return (0);
}

void	find_command_utils(t_params *data, t_quotes *quot, int i, int flag)
{
	quot->start = i;
	while (data->line[i])
	{
		if ((data->line[i] == '>' || data->line[i] == '<') && !flag)
		{
			quot->end = i;
			data->node->need_to_assign = 1;
			return ;
		}
		if (data->line[i] == '\r' && flag)
			flag = 0;
		else if (data->line[i] == '\r' && !flag && check_ahead(data->line, i))
			flag = 1;
		if ((is_nothing(data->line[i]) || data->line[i + 1] == '\0') && !flag)
		{
			quot->end = i;
			return ;
		}
		i++;
	}
}

void	find_command(t_params *data, t_quotes *quot)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (is_nothing(data->line[i]))
		i++;
	if (data->line[i] == '\r' && data->line[i + 1] == '\r'
		&& data->line[i + 2] != '\r'
		&& (is_nothing(data->line[i + 2]) || !data->line[i + 2]))
	{
		data->line[i] = '\'';
		data->line[i + 1] = '\'';
		data->key = 0;
	}
	if (data->line[i])
		find_command_utils(data, quot, i, flag);
}

void	fill_command_utils(t_params *data, t_quotes *quot)
{
	data->node->cmd = malloc(2);
	data->node->cmd[0] = ' ';
	data->node->cmd[1] = '\0';
	quot->start += 2;
	return ;
}

void	fill_command(t_params *data, t_quotes *quot)
{
	int	i;
	int	end;

	end = quot->end;
	if (data->node->need_to_assign || somethind_ahead(data->line, end))
		end--;
	if (!data->key)
	{
		fill_command_utils(data, quot);
		return ;
	}
	data->node->cmd = malloc(end - quot->start + 2);
	i = 0;
	while (quot->start <= end)
	{
		if (data->line[quot->start] != '\r')
		{
			if (data->line[quot->start] == '\a')
				data->line[quot->start] = '?';
			data->node->cmd[i] = data->line[quot->start];
			i++;
		}
		quot->start++;
	}
	data->node->cmd[i] = '\0';
}
