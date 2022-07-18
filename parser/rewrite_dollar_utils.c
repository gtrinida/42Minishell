/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_dollar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 06:57:55 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 07:19:30 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char *bf_dollar, char *af_dollar, char *instead_of)
{
	int	len;

	len = 0;
	if (bf_dollar != NULL)
		len += ft_strlen(bf_dollar);
	len += ft_strlen(instead_of);
	if (af_dollar != NULL)
		len += ft_strlen(af_dollar);
	return (len);
}

void	rewrite_new_line_utils(char *af_dollar, int i, t_params *data)
{
	int	j;

	j = 0;
	if (af_dollar)
	{
		while (af_dollar[j])
		{
			data->line[i] = af_dollar[j];
			j++;
			i++;
		}
		free(af_dollar);
	}
	data->line[i] = '\0';
}

void	rewrite_new_line(char *bf_dollar, int *i,
	char *instead_of, t_params *data)
{
	int	j;

	j = 0;
	*i = 0;
	if (bf_dollar)
	{
		while (bf_dollar[*i])
		{
			data->line[*i] = bf_dollar[*i];
			(*i)++;
		}
		free(bf_dollar);
	}
	while (instead_of[j])
	{
		data->line[*i] = instead_of[j];
		(*i)++;
		j++;
	}
	free(instead_of);
}
