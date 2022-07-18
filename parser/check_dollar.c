/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:10:48 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 05:02:07 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dollar(char *line, int i, int steps_next_quote, int count)
{
	char	flag;

	flag = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			flag = line[i];
			count++;
			steps_next_quote--;
		}
		if (line[i] == '$' && line[i + 1] == flag
			&& flag && steps_next_quote != 0)
		{
			if (is_nothing(line[i + 2])
				|| line[i + 2] == flag)
			{	
				steps_next_quote += count;
				if (even_or_odd(count))
					line[i] = ' ';
			}
		}
		i++;
	}
}
