/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 06:18:34 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/25 22:24:08 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_correct_status(int exit_status)
{
	if (exit_status >= 0)
	{
		if (WIFEXITED(exit_status) && !WEXITSTATUS(exit_status)
			&& !WIFSIGNALED(exit_status))
				g_status = 0;
		else
		{
			g_status = WEXITSTATUS(exit_status);
			if (WIFSIGNALED(exit_status))
				g_status = exit_status + 128;
		}
	}
}

char	*get_last_argv(char *cmd, char **argv, int n_arg)
{
	if (!n_arg)
		return (ft_strdup(cmd));
	return (ft_strdup(argv[n_arg - 1]));
}

int	end_exec(t_params *data, t_std_backup *std_backup, int exit_status)
{
	if (stdbackup_set(std_backup) || stdbackup_close(std_backup))
	{
		print_error(data->list->cmd, errno, NULL);
		exit_minishell(data, M_ERR);
	}
	if (sighandler_set(DEFAULT_MODE))
	{
		print_error(data->list->cmd, errno, NULL);
		exit_minishell(data, M_ERR);
	}
	get_correct_status(exit_status);
	if (g_status == 130)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else if (g_status == 131)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	redirect_clear(data->list);
	return (M_OK);
}

int	start_rdir(t_params *data, t_std_backup *std_backup)
{
	int	err;

	err = pipeline_set_fd(data->minishell, data->list);
	if (err)
	{
		if (err != HEREDOC_ERR)
		{
			print_error(data->list->cmd, errno, NULL);
			errno = 0;
		}
		if (stdbackup_set(std_backup))
		{
			print_error(data->list->cmd, errno, NULL);
			exit_minishell(data, M_ERR);
		}
		g_status = 1;
		return (g_status);
	}
	return (M_OK);
}

void	change_underscore(t_params *data)
{
	if (!data->list->next)
	{
		envlist_change_val(data->minishell->env_list, "_",
			get_last_argv(data->list->cmd, data->list->arg,
				data->list->arg_count));
	}
	else
		envlist_change_val(data->minishell->env_list, "_", ft_strdup(""));
}
