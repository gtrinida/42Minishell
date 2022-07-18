/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_qout_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:38:30 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 04:53:11 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_after_second_utils(char *line, int *i_tmp, char sym, int *bf)
{
	while (*i_tmp)
	{
		if (line[*i_tmp] == sym)
		{
			*bf = 1;
			break ;
		}
		(*i_tmp)--;
	}
}

void	before_after_utils(char *line, int *i, char sym, int *af)
{
	while (line[*i])
	{
		if (line[*i] == sym)
		{
			*af = 1;
			break ;
		}
		(*i)++;
	}
}

int	before_after(char *line, int i, int type)
{
	int	i_tmp;
	int	bf;
	int	af;
	int	sym;

	if (type == '\"')
		sym = '\'';
	else
		sym = '\"';
	bf = 0;
	af = 0;
	i_tmp = i;
	before_after_utils(line, &i, sym, &af);
	before_after_second_utils(line, &i_tmp, sym, &bf);
	if (line[i_tmp] == sym)
		bf = 1;
	if (bf && af)
		return (1);
	return (0);
}
