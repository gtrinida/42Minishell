/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:51 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:42:49 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_params *data, t_node *pipe_line)
{
	t_env_list	*ptr;

	if (pipe_line->arg[1])
	{
		print_error(pipe_line->arg[0], USAGE_ERROR, pipe_line->arg[1]);
		return (BUILTIN_FAIL);
	}
	ptr = data->minishell->env_list;
	while (ptr)
	{
		if (ptr->val)
		{
			ft_putstr_fd(ptr->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(ptr->val, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		ptr = ptr->next;
	}
	return (M_OK);
}
