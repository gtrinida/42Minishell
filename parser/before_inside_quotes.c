/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_inside_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:45:53 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 07:52:41 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_quotes(t_params *data, t_quotes *quot, int i, char *line)
{
	if (is_nothing(line[i + 2]) || !line[i + 2])
	{
		data->line[quot->j] = line[quot->i];
		quot->j++;
		quot->i++;
		data->line[quot->j] = line[quot->i];
		quot->j++;
		quot->i++;
		quot->flag = 0;
		data->key = 0;
		return (0);
	}
	return (1);
}

int	before_inside_utils(char *line, t_params *data, t_quotes *quot)
{
	int	i;

	if (!data->key)
		return (1);
	i = quot->i;
	if (i > 0)
	{
		if (!check_command_before(line, i))
			return (1);
	}
	if (line[i] == '\'')
	{
		if (line[i + 1] == '\'')
			return (write_quotes(data, quot, i, line));
	}
	if (line[i] == '\"')
	{
		if (line[i + 1] == '\"')
			return (write_quotes(data, quot, i, line));
	}
	return (1);
}

int	check_flag_bf(char *line, t_quotes *quot)
{
	if (line[quot->i + 1] == quot->flag && !is_nothing(line[quot->i + 2])
		&& !is_rdir(line[quot->i + 2]))
	{
		if (quot->flag != line[quot->i + 2])
		{
			quot->i += 2;
			return (0);
		}
		quot->i += 2;
	}
	return (1);
}

void	before_inside(t_quotes *quot, t_params *data, char *line, char **env)
{
	quot->flag = line[quot->i];
	if (!before_inside_utils(line, data, quot))
		return ;
	if (!dollar_in_double_quotes(quot, line))
		return ;
	if (!check_flag_bf(line, quot))
		return ;
	if (we_need_this_quotes(line, quot->i, quot->flag)
		|| heredock_behind(line, quot->i))
	{
		quot->pass_quote = 1;
		data->line[quot->j] = line[quot->i];
		quot->j++;
	}
	else if (we_need_this_quotes(line, quot->i + 1, quot->flag)
		|| heredock_behind(line, quot->i))
	{
		quot->pass_quote = 1;
		data->line[quot->j] = line[quot->i + 1];
		quot->j++;
		quot->i++;
	}
	quot->i++;
	if (line[quot->i] == '$')
		work_with_dollar(quot, line, data, env);
}
