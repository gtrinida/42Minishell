/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_dollar_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 20:45:09 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_line(char *line, char *line_to_copy, t_quotes *quot)
{
	int	end;
	int	i;

	i = 0;
	end = quot->i;
	while (end)
	{
		line[i] = line_to_copy[i];
		i++;
		end--;
	}
	line[i] = '\0';
}

int	next_quot_check(char *line, int i)
{
	char	flag;
	int		counter;

	counter = 1;
	flag = line[i];
	i++;
	while (line[i])
	{
		if (line[i] == flag)
			counter++;
		i++;
	}
	if (even_or_odd(counter))
		return (0);
	return (1);
}

int	it_is_env(t_quotes *quot, t_params *data, char *line, char **env)
{
	get_env(data, quot, line, env);
	if (is_dollar_ahead(line, quot->i))
		check_flag(data, quot, line);
	if (line[quot->i] == '$' && (is_nothing(line[quot->i + 1])
			|| !line[quot->i + 1]))
	{
		if (!is_dollar_ahead(line, quot->i + 1))
			return (0);
	}
	return (1);
}

int	start_command_utils(t_quotes *quot, t_params *data, char *line, char **env)
{
	if (is_it_env(env, line, get_finish(line, quot->i), quot->i))
	{
		if (!it_is_env(quot, data, line, env))
			return (0);
	}
	else if (!is_it_env(env, line, get_finish(line, quot->i), quot->i))
	{
		if (!not_env(quot, data, line))
			return (0);
	}
	else
	{
		quot->i = get_finish(line, quot->i) + 1;
		return (0);
	}
	return (1);
}

int	start_command(t_quotes *quot, t_params *data, char *line, char **env)
{
	while (line[quot->i])
	{
		if (!is_nothing(line[quot->i]) && line[quot->i - 1] == '$')
		{
			if (!start_command_utils(quot, data, line, env))
				return (0);
		}
		if (!is_dollar_ahead(line, quot->i))
		{
			if (line[quot->i] == quot->flag)
			{	
				quot->flag = 0;
				write_one_sym(data, quot, line);
			}
			return (0);
		}
		quot->i++;
	}
	return (0);
}
