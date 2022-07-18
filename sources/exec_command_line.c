/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:59 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/25 23:51:22 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_exec_pipe(t_params *data)
{
	int		exit_status;
	t_node	*head;

	head = data->list;
	if (head->next)
		pipe_exec(data, head, pipe_desc_init(PIPE, -1, -1, -1));
	else
		pipe_exec(data, head, pipe_desc_init(SIMPLE, -1, -1, -1));
	while (head)
	{
		if (head->pid > 0)
		{
			if (head->next)
			{
				if (waitpid(head->pid, NULL, WUNTRACED) < 0)
					return (M_ERR);
			}
			else if (waitpid(head->pid, &exit_status, WUNTRACED) < 0)
				return (M_ERR);
		}
		head = head->next;
	}
	return (exit_status);
}

int	get_status(t_params *data)
{
	int	exit_status;

	exit_status = -1;
	exit_status = start_exec_pipe(data);
	if (exit_status < 0)
	{
		print_error(data->list->cmd, errno, NULL);
		exit_minishell(data, M_ERR);
	}
	return (exit_status);
}

int	exec_pipe_line(t_params *data)
{
	t_std_backup	std_backup;
	int				exit_status;

	exit_status = -1;
	if (!data->list)
		return (M_OK);
	if (stdbackup_copy(&std_backup))
	{
		print_error(data->list->cmd, errno, NULL);
		exit_minishell(data, M_ERR);
	}
	if (start_rdir(data, &std_backup))
		return (g_status);
	change_underscore(data);
	if (!data->list->next && is_builtin(data->list->cmd) >= 0)
		exit_status = exec_cmd(data, data->list, -1, -1);
	else
		exit_status = get_status(data);
	end_exec(data, &std_backup, exit_status);
	return (g_status);
}
