/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:20 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:47:13 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_params *data, t_node *pipe_line)
{
	char	path[PATH_MAX + 1];

	(void)data;
	if (pipe_line->arg[1])
	{
		print_error(pipe_line->arg[0], USAGE_ERROR,
			pipe_line->arg[1]);
		return (BUILTIN_FAIL);
	}
	if (getcwd(path, PATH_MAX + 1) != NULL)
		ft_putendl_fd(path, STDOUT_FILENO);
	else
	{
		print_error(pipe_line->arg[0], errno, NULL);
		errno = 0;
		return (BUILTIN_FAIL);
	}
	return (M_OK);
}
