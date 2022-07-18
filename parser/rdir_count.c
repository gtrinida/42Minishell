/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:20:13 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 23:16:22 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_rdir(char sym)
{
	if (sym == '>' || sym == '<')
		return (1);
	return (0);
}

void	correct_count_rdir(t_params *data, int *i)
{
	if (is_rdir(data->line[*i + 1]) && (is_nothing(data->line[*i + 2])
			|| data->line[*i + 2] == '\r'))
	{
		data->node->n_rdir_arg += 1;
		(*i)++;
	}
	else if (is_nothing(data->line[*i + 1]))
		data->node->n_rdir_arg += 2;
	(*i)++;
}

void	correct_count_utils(t_params *data, int *i)
{
	if (is_nothing(data->line[*i - 1]))
	{
		if (is_rdir(data->line[*i + 1]) && (is_nothing(data->line[*i + 2])
				|| data->line[*i + 2] == '\r'))
		{
			data->node->n_rdir_arg += 2;
			(*i)++;
		}
		else if (is_nothing(data->line[*i + 1]))
			data->node->n_rdir_arg += 2;
		else if (!is_nothing(data->line[*i + 1])
			&& !is_rdir(data->line[*i + 1]))
			data->node->n_rdir_arg += 1;
		(*i)++;
		return ;
	}
	if (!is_nothing(data->line[*i - 1]))
		correct_count_rdir(data, i);
}

void	correct_count(t_params *data, int *i)
{
	if (*i > 0)
		return (correct_count_utils(data, i));
	else
	{
		if (is_nothing(data->line[*i + 1]))
		{
			data->node->n_rdir_arg += 2;
			(*i)++;
			return ;
		}
		if (is_rdir(data->line[*i + 1]) && is_nothing(data->line[*i + 2]))
		{
			data->node->n_rdir_arg += 2;
			*i += 2;
			return ;
		}	
	}
	return ;
}
