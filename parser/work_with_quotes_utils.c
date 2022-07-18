/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:45:53 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 07:43:26 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	param_init(t_quotes *quot)
{
	quot->i_arg = 0;
	quot->len_env = 0;
	quot->env_i = 0;
	quot->pass_quote = 0;
	quot->flag = 0;
	quot->i = 0;
	quot->j = 0;
	quot->start = 0;
	quot->end = 0;
}

int	check_command_before(char *line, int i)
{
	i--;
	while (i >= 0)
	{
		if (!is_nothing(line[i]))
			return (0);
		i--;
	}
	return (1);
}
