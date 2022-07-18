/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_dollar_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:45:53 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 04:33:17 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_in_double_quotes(t_quotes *quot, char *line)
{
	if (line[quot->i + 1] == quot->flag && line[quot->i + 2] == '$')
	{
		if (line[quot->i + 3] == quot->flag && line[quot->i + 4] == quot->flag)
		{
			quot->i += 5;
			quot->flag = 0;
			return (0);
		}
	}
	return (1);
}

void	find_new_command_utills(t_quotes *quot, t_params *data, char *line)
{
	if (!line[quot->i - 1])
		return ;
	if (!line[quot->i])
		return ;
	if (line[quot->i + 1])
	{
		if (line[quot->i] == quot->flag && !line[quot->i + 1] && quot->flag)
		{
			data->line[quot->j] = line[quot->i];
			quot->j++;
			quot->i++;
			quot->flag = 0;
		}
		else if (line[quot->i + 1] == quot->flag && line[quot->i + 2] == '$')
		{
			data->line[quot->j] = line[quot->i];
			quot->j++;
			quot->i++;
			quot->flag = 0;
		}
		if (line[quot->i] == quot->flag)
			quot->flag = 0;
	}
}

int	check_multi_dollars(char *line, t_quotes *quot, t_params *data, int counter)
{
	if (line[quot->i + 1] != '$')
		return (1);
	while (line[quot->i] == '$')
	{
		counter++;
		if (line[quot->i + 1] != '$')
		{
			if (even_or_odd(counter))
			{
				quot->i++;
				return (0);
			}
			else
			{
				if (line[quot->i + 1] == '\'' || line[quot->i + 1] == '\"')
				{
					data->line[quot->j] = '$';
					quot->j++;
				}
				return (1);
			}
		}
		quot->i++;
	}
	return (1);
}

void	find_new_command(t_quotes *quot, t_params *data, char *line, char **env)
{	
	quot->i++;
	start_command(quot, data, line, env);
	find_new_command_utills(quot, data, line);
}
