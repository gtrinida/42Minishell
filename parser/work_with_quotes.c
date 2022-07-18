/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:45:53 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/21 01:05:40 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_utils(char *line, t_quotes *quot, t_params *data, char **env)
{
	int	len;

	len = ft_strlen(line);
	if (line[quot->i] == '$')
	{
		work_with_dollar(quot, line, data, env);
	}
	if (quot->i < len)
	{
		if (line[quot->i] == quot->flag)
			quot->pass_quote = 0;
		data->line[quot->j] = line[quot->i];
		quot->j++;
	}
}

void	inside_quotes(char *line, t_quotes *quot, t_params *data, char **env)
{
	if (line[quot->i] == quot->flag)
	{
		quot->flag = 0;
		if (quot->pass_quote)
		{
			data->line[quot->j] = line[quot->i];
			quot->j++;
			quot->pass_quote = 0;
		}
		else if (line[quot->i + 1] == '$')
		{
			quot->i++;
			work_with_dollar(quot, line, data, env);
			quot->i--;
		}
	}
	else
		inside_utils(line, quot, data, env);
	if (quot->i >= (int)ft_strlen(line))
	{
		quot->i = ft_strlen(line);
		return ;
	}
	quot->i++;
}

void	not_quotes(char *line, t_quotes *quot, t_params *data)
{
	if (line[quot->i] == '$' && !is_nothing(line[quot->i + 1]))
	{
		if (line[quot->i + 1] == '\0')
		{
			data->line[quot->j] = line[quot->i];
			quot->i++;
			quot->j++;
		}
		return ;
	}
	if (!is_nothing(line[quot->i]) && line[quot->i])
	{	
		data->line[quot->j] = line[quot->i];
		quot->j++;
		quot->i++;
	}
	if (is_nothing(line[quot->i]) && line[quot->i])
	{
		if (!is_nothing(line[quot->i + 1]) && line[quot->i + 1])
		{
			data->line[quot->j] = line[quot->i];
			quot->j++;
		}
		quot->i++;
	}
}
