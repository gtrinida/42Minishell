/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 21:00:30 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_dollar_ahead(t_params *data, t_quotes *quot, char *line)
{
	while (line[quot->i])
	{
		if (line[quot->i] == quot->flag)
		{
			quot->flag = 0;
			write_one_sym(data, quot, line);
			break ;
		}
		if (line[quot->i - 1] == '$' && ft_isdigit(line[quot->i]))
		{
			quot->i += 1;
			return (0);
		}
		if (is_nothing(line[quot->i]))
			return (0);
		if (quot->flag && line[quot->i] == quot->flag)
		{
			quot->flag = 0;
			return (0);
		}
		quot->i++;
	}
	return (0);
}

int	not_env_cycle_utils(t_quotes *quot, t_params *data, char *line)
{
	if (quot->flag && (line[quot->i] == '\'' || is_nothing(line[quot->i])))
	{
		while (line[quot->i] != '$')
		{
			if (line[quot->i] == quot->flag)
				break ;
			write_one_sym(data, quot, line);
		}
		if (line[quot->i] == '$' && (line[quot->i + 1] == quot->flag
				|| is_nothing(line[quot->i + 1])))
			write_one_sym(data, quot, line);
		else if (line[quot->i] == '$')
			return (1);
	}
	if (line[quot->i] == quot->flag)
	{
		quot->flag = 0;
		write_one_sym(data, quot, line);
		if (line[quot->i] == '$')
			return (1);
		return (0);
	}
	return (-1);
}

int	not_env_cycle(t_quotes *quot, t_params *data, char *line)
{
	int	do_break;

	do_break = 0;
	while (line[quot->i] != '$')
	{
		do_break = not_env_cycle_utils(quot, data, line);
		if (do_break == 0)
			return (0);
		if (do_break == 1)
			break ;
		if (is_nothing(line[quot->i]) && !quot->flag)
			return (0);
		if (line[quot->i + 1] == '$')
		{
			if (!line[quot->i + 2])
			{
				quot->i += 1;
				return (0);
			}
			if (!is_nothing(line[quot->i + 2]))
				break ;
		}
		quot->i++;
	}
	return (1);
}

int	not_env(t_quotes *quot, t_params *data, char *line)
{
	if (line[quot->i - 1] == '$' && line[quot->i] == '\"'
		&& next_quot_check(line, quot->i))
	{
		data->line[quot->j] = line[quot->i - 1];
		quot->j++;
	}
	if (!is_dollar_ahead(line, quot->i))
		return (not_dollar_ahead(data, quot, line));
	if (!not_env_cycle(quot, data, line))
		return (0);
	if (!line[quot->i + 1] || is_nothing(line[quot->i + 1]))
	{
		data->line[quot->j] = line[quot->i];
		quot->j++;
		if (line[quot->i] == '$' && !line[quot->i + 1])
		{
			quot->i += 1;
			return (0);
		}
		if (!line[quot->i + 1])
			return (0);
		quot->i++;
		return (0);
	}
	return (1);
}
