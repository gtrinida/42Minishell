/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_rdir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:20:13 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 03:52:14 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quots_with_heredoc(char *line, int i)
{
	while (is_nothing(line[i]))
		i++;
	if (line[i] == '\r')
		return (1);
	return (0);
}

void	fill_agrunent_rdir_utils(t_rdir *tmp, t_quotes *quot, t_params *data)
{
	int	i;
	int	end;

	end = quot->end;
	i = 0;
	if (somethind_ahead(data->line, end))
		end--;
	while (quot->start <= end)
	{
		if (data->line[quot->start] != '\r')
		{
			if (data->line[quot->start] == '\a')
				data->line[quot->start] = '?';
			tmp->arg[i] = data->line[quot->start];
			i++;
		}
		quot->start++;
	}
	tmp->arg[i] = '\0';
}

void	fill_argument_rdir(t_params *data, t_quotes *quot, int type)
{
	t_rdir	*tmp;

	tmp = data->node->rdir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->arg = malloc(quot->end - quot->start + 2);
	fill_agrunent_rdir_utils(tmp, quot, data);
	if (type == 5)
	{
		tmp->type = 1;
		tmp->heredock_quote = 1;
		return ;
	}
	tmp->type = type;
}

void	start_work_rdir_utils(t_params *data, t_quotes *quot,
	int type, int plus_end)
{
	quot->start = quot->end + plus_end;
	find_arguments(data, quot);
	fill_argument_rdir(data, quot, type);
}

void	start_work_rdir(t_params *data, t_quotes *quot)
{
	add_rdir(&(data->node->rdir));
	if (data->line[quot->end] == '>' && data->line[quot->end + 1] != '>')
		return (start_work_rdir_utils(data, quot, 2, 1));
	if (data->line[quot->end] == '>' && data->line[quot->end + 1] == '>')
		return (start_work_rdir_utils(data, quot, 3, 2));
	if (data->line[quot->end] == '<' && data->line[quot->end + 1] != '<')
		return (start_work_rdir_utils(data, quot, 0, 1));
	if (data->line[quot->end] == '<' && data->line[quot->end + 1] == '<')
	{
		if (quots_with_heredoc(data->line, quot->end + 2))
			return (start_work_rdir_utils(data, quot, 5, 2));
		return (start_work_rdir_utils(data, quot, 1, 2));
	}
}
