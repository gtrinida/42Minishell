/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:17 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:47:50 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_desc	*pipe_desc_init(int exec_type, int fd_in,
	int fd_out, int fd_to_close)
{
	t_pipe_desc	*pipe_desc;

	pipe_desc = (t_pipe_desc *)malloc(sizeof(t_pipe_desc));
	if (pipe_desc)
	{
		pipe_desc->exec_type = exec_type;
		pipe_desc->fd_in = fd_in;
		pipe_desc->fd_out = fd_out;
		pipe_desc->fd_to_close = fd_to_close;
	}
	return (pipe_desc);
}

static void	next_pipe(
	t_params *data,
	t_node *node,
	t_pipe_desc *pipe_desc,
	int p[2])
{
	if (((t_node *)node->next)->next)
	{
		pipe_exec(data, node->next,
			pipe_desc_init(PIPE, p[READ_END], pipe_desc->fd_out, -1));
	}
	else
	{
		pipe_exec(data, node->next,
			pipe_desc_init(SIMPLE, p[READ_END], pipe_desc->fd_out, -1));
		if (safe_close(p[READ_END]))
		{
			print_error(node->cmd, errno, NULL);
			exit_minishell(data, M_ERR);
		}
	}	
}

int	pipe_exec(t_params *data, t_node *node, t_pipe_desc *pipe_desc)
{
	int	p[2];

	if (pipe_desc->exec_type == PIPE)
	{
		if (pipe(p))
		{
			print_error(node->cmd, errno, NULL);
			exit_minishell(data, M_ERR);
		}
		pipe_exec(data, node, pipe_desc_init(SIMPLE, pipe_desc->fd_in,
				p[WRITE_END], p[READ_END]));
		if (safe_close(p[WRITE_END]) || safe_close(pipe_desc->fd_in))
		{
			print_error(node->cmd, errno, NULL);
			exit_minishell(data, M_ERR);
		}
		next_pipe(data, node, pipe_desc, p);
	}
	else if (exec_in_fork(data, node, pipe_desc))
	{
		print_error(node->cmd, errno, NULL);
		exit_minishell(data, M_ERR);
	}
	free(pipe_desc);
	return (M_OK);
}

int	redirect_pipe(int fd_in, int fd_out)
{
	if (fd_in >= 0)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0 || close(fd_in))
			return (M_ERR);
	}
	if (fd_out >= 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) < 0 || close(fd_out))
			return (M_ERR);
	}
	return (M_OK);
}
