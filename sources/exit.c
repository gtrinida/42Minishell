/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:02 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 06:35:52 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exiting(t_params *data, t_node *pipe_line)
{
	int				i;
	unsigned char	exit_status;

	i = 0;
	while (pipe_line->arg[1][i])
	{
		if (!ft_isdigit(pipe_line->arg[1][i])
			&& !(i == 0 && pipe_line->arg[1][i] == '-'))
		{
			print_error(pipe_line->arg[0], NOT_NUM_ARG, pipe_line->arg[1]);
			exit_minishell(data, 255);
		}
		++i;
	}
	if (pipe_line->arg[2])
	{
		print_error(pipe_line->arg[0], TOO_MANY_ARGS, NULL);
		return (M_ERR);
	}
	exit_status = ft_atoi(pipe_line->arg[1]);
	exit_minishell(data, exit_status);
	return (M_ERR);
}

int	ft_exit(t_params *data, t_node *pipe_line)
{
	int	i;

	i = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!pipe_line->arg[1])
		exit_minishell(data, g_status);
	while (ft_isspace(pipe_line->arg[1][i]))
		++i;
	if (check_overflow(pipe_line->arg[1]) == M_ERR)
	{
		print_error(pipe_line->arg[0], NOT_NUM_ARG, pipe_line->arg[1]);
		exit_minishell(data, 255);
	}
	exiting(data, pipe_line);
	return (M_ERR);
}
