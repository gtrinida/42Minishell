/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:32 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/25 21:07:15 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_params *data, t_node *pipe_line)
{
	int	i;
	int	err;

	i = 1;
	err = M_OK;
	while (i < pipe_line->arg_count)
	{
		if (envvar_validate(pipe_line->arg[i]))
		{
			err = M_ERR;
			print_error(pipe_line->arg[0], INVALID_IDENTIFER,
				pipe_line->arg[i]);
		}
		else
			envlist_delone(data->minishell, pipe_line->arg[i]);
		++i;
	}
	return (err);
}
