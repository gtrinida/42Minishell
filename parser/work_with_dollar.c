/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:45:53 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 05:27:00 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	work_with_dollar_outside(char *line, t_quotes *quot,
	t_params *data, char **env)
{
	if (line[quot->i] == '$')
	{	
		if (line[quot->i + 1] == '?')
		{
			write_one_sym(data, quot, line);
			write_one_sym(data, quot, line);
			return ;
		}
		if (!check_multi_dollars(line, quot, data, 0))
			return ;
		if (ft_isdigit(line[quot->i + 1]))
			quot->i += 2;
		else if (line[quot->i + 1] == '\'' || line[quot->i + 1] == '\"')
			quot->i += 1;
		else if (is_it_letter(line[quot->i + 1])
			|| is_it_specsym(line[quot->i + 1]))
		{
			find_new_command(quot, data, line, env);
		}
	}
}

void	wwd_double_utils(t_params *data, t_quotes *quot, char *line, char **env)
{
	if (line[quot->i] == '$' && !ft_isdigit(line[quot->i + 1])
		&& !is_nothing(line[quot->i + 1]) && line[quot->i + 1])
	{
		if (line[quot->i + 1] == '\''
			|| line[quot->i + 1] == '\"')
			return ;
		if (line[quot->i] == '$' && line[quot->i + 1] == '?')
		{
			data->line[quot->j] = line[quot->i];
			quot->j++;
			quot->i++;
			data->line[quot->j] = line[quot->i];
			quot->j++;
			quot->i++;
			return ;
		}
		check_multi_dollars(line, quot, data, 0);
		find_new_command(quot, data, line, env);
	}
}

void	wwd_double(t_params *data, t_quotes *quot, char *line, char **env)
{
	if (line[quot->i + 1] == quot->flag)
		return ;
	if (line[quot->i] == '$' && ft_isdigit(line[quot->i + 1]))
	{
		quot->i += 2;
		if (line[quot->i] == quot->flag)
		{
			if (line[quot->i + 1] != quot->flag)
			{
				data->line[quot->j] = line[quot->i];
				quot->j++;
			}
			quot->flag = 0;
			quot->i++;
		}
	}
	wwd_double_utils(data, quot, line, env);
}

int	wwd_single(t_params *data, t_quotes *quot, char *line)
{
	while (quot->flag)
	{
		if (!line[quot->i])
			return (0);
		if (line[quot->i] == quot->flag)
		{
			if (line[quot->i + 1] != quot->flag)
			{
				data->line[quot->j] = line[quot->i];
				quot->j++;
			}
			quot->flag = 0;
			quot->i++;
			break ;
		}
		data->line[quot->j] = line[quot->i];
		quot->j++;
		quot->i++;
	}
	return (1);
}

void	work_with_dollar(t_quotes *quot, char *line, t_params *data, char **env)
{
	if (quot->flag == '\'')
	{
		if (!wwd_single(data, quot, line))
			return ;
	}
	if ((quot->flag == '\"' || !quot->flag) && line[quot->i])
		wwd_double(data, quot, line, env);
}
