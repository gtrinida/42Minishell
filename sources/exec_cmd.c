/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:56 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/26 00:07:55 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

char	*f_path(t_params *data, t_node *pipe_line)
{
	int		err;
	char	*path_to_cmd;

	err = find_cmd(pipe_line->cmd, data->minishell->env_list, &path_to_cmd);
	if (err == EACCES)
	{
		print_error(pipe_line->cmd, EACCES, NULL);
		exit_minishell(data, 126);
	}
	if (err == ENOENT)
	{
		print_error(pipe_line->cmd, ENOENT, NULL);
		exit_minishell(data, 127);
	}
	if (!is_regular_file(path_to_cmd))
	{
		print_error(pipe_line->cmd, ISDIR, NULL);
		free(path_to_cmd);
		exit_minishell(data, 126);
	}
	return (path_to_cmd);
}

int	exec_cmd(t_params *data, t_node *pipe_line,
	int fd_in, int fd_out)
{
	int		err;
	int		built_in;
	char	*path_to_cmd;

	path_to_cmd = NULL;
	pipe_line->arg = argv_crutch(pipe_line->arg, pipe_line->cmd,
			pipe_line->arg_count);
	pipe_line->arg_count++;
	if (!pipe_line->need_to_free_arg)
		pipe_line->need_to_free_arg++;
	if (redirect_pipe(fd_in, fd_out) || cmd_redirect_s(pipe_line->rdir))
		return (M_ERR);
	built_in = is_builtin(pipe_line->cmd);
	if (built_in >= 0)
	{
		err = data->minishell->built_in[built_in](data, pipe_line);
		return (err);
	}
	path_to_cmd = f_path(data, pipe_line);
	envarr_change_val(data->minishell->env_arr, "_", path_to_cmd);
	execve(path_to_cmd, pipe_line->arg, data->minishell->env_arr);
	print_error(pipe_line->cmd, errno, NULL);
	exit_minishell(data, M_ERR);
	return (M_ERR);
}

int	exec_in_fork(t_params *data, t_node *pipe_line,
	t_pipe_desc *pipe_desc)
{
	int	err;

	pipe_line->pid = fork();
	if (pipe_line->pid > 0)
	{
		sighandler_set(EXEC_MODE_PARENT);
		if (cmd_redirect_close(pipe_line->rdir))
			return (M_ERR);
		return (M_OK);
	}
	else if (pipe_line->pid == 0)
	{
		errno = 0;
		sighandler_set(EXEC_MODE_CHILD);
		safe_close(pipe_desc->fd_to_close);
		err = exec_cmd(data, pipe_line, pipe_desc->fd_in,
				pipe_desc->fd_out);
		exit_minishell(data, err);
	}
	else
	{
		print_error(pipe_line->cmd, errno, NULL);
		exit_minishell(data, M_ERR);
	}
	return (M_ERR);
}
