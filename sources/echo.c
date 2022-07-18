/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/25 21:06:19 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_params *data, t_node *pipe_line)
{
	int	i;
	int	flag;

	(void)data;
	i = 1;
	flag = 0;
	while (i < pipe_line->arg_count && !strcmp(pipe_line->arg[i], "-n"))
	{
		++flag;
		++i;
	}
	if (i < pipe_line->arg_count)
	{
		ft_putstr_fd(pipe_line->arg[i], STDOUT_FILENO);
		++i;
		while (pipe_line->arg[i])
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(pipe_line->arg[i], STDOUT_FILENO);
			++i;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (M_OK);
}
