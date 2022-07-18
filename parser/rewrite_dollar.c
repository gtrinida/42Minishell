/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:47:30 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 07:19:23 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*write_af(int *i, t_params *data)
{
	char	*af_dollar;
	int		j;

	j = 0;
	if (data->line[*i + 2])
	{
		af_dollar = malloc(ft_strlen(data->line) - (*i + 2) + 1);
		*i += 2;
		while (data->line[*i])
		{
			af_dollar[j] = data->line[*i];
			(*i)++;
			j++;
		}
		af_dollar[j] = '\0';
		j = 0;
	}
	else
		af_dollar = NULL;
	return (af_dollar);
}

char	*write_bf(int i, t_params *data)
{
	int		j;
	char	*bf_dollar;

	j = 0;
	if (i > 1)
	{
		bf_dollar = malloc(i + 1);
		while (j < i)
		{
			bf_dollar[j] = data->line[j];
			j++;
		}
		bf_dollar[j] = '\0';
	}
	else
		bf_dollar = NULL;
	return (bf_dollar);
}

void	rewrite(t_params *data, int i)
{
	char	*bf_dollar;
	char	*af_dollar;
	char	*instead_of;
	int		len;

	bf_dollar = write_bf(i, data);
	af_dollar = write_af(&i, data);
	instead_of = ft_itoa(g_status);
	len = get_len(bf_dollar, af_dollar, instead_of);
	free(data->line);
	data->line = malloc(len + 2);
	rewrite_new_line(bf_dollar, &i, instead_of, data);
	rewrite_new_line_utils(af_dollar, i, data);
}

void	check_dollar_with_single(t_params *data, int i)
{
	if (data->line[i + 1] == '\0')
		return ;
	i++;
	while (data->line[i])
	{
		if (data->line[i] == '\'')
		{
			return ;
		}
		if (data->line[i] == '$')
		{
			if (data->line[i + 1] == '?')
			{
				i++;
				data->line[i] = '\a';
				return ;
			}
		}
		i++;
	}
}

void	check_dollar_with_quest(t_params *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == '$')
		{
			if (data->line[i + 1] == '?')
				rewrite(data, i);
		}
		i++;
	}
}
