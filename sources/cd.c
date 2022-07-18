/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:30 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 06:32:15 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*uwu(t_minishell *minishell, t_node *pipe_line,
	char *current_path, char *env_path)
{
	char	*target_path;

	target_path = NULL;
	if (ft_strcmp(pipe_line->arg[1], "-") == 0)
	{
		env_path = ft_getenv(minishell->env_list, "OLDPWD");
		if (!env_path)
			print_error(pipe_line->arg[0], NO_OLDPWD_VAR, NULL);
		else
			target_path = ft_strdup(env_path);
	}
	else if (pipe_line->arg[1][0] == '/')
		target_path = ft_strdup(pipe_line->arg[1]);
	else
	{
		ft_strlcat(current_path, "/", PATH_MAX + 2);
		target_path = ft_strjoin(current_path, pipe_line->arg[1]);
	}
	return (target_path);
}

static char	*create_target_path(t_minishell *minishell,
	t_node *pipe_line, char *current_path)
{
	char	*env_path;
	char	*target_path;

	target_path = NULL;
	env_path = NULL;
	if (!pipe_line->arg[1])
	{
		env_path = ft_getenv(minishell->env_list, "HOME");
		if (!env_path)
			print_error(pipe_line->arg[0], NO_HOME_VAR, NULL);
		else
			target_path = ft_strdup(env_path);
		return (target_path);
	}
	target_path = uwu(minishell, pipe_line, current_path, env_path);
	return (target_path);
}

static int	chd(t_minishell *minishell, t_node *pipe_line,
	char *target_path, char	*current_path)
{
	envlist_change_val(minishell->env_list, "OLDPWD", ft_strdup(current_path));
	chdir(target_path);
	free(target_path);
	if (!errno)
	{
		if (!getcwd(current_path, PATH_MAX + 1))
			return (BUILTIN_FAIL);
		envlist_change_val(minishell->env_list, "PWD", ft_strdup(current_path));
	}
	else
	{
		print_error(pipe_line->arg[0], errno, pipe_line->arg[1]);
		errno = 0;
		return (BUILTIN_FAIL);
	}
	return (M_OK);
}

int	ft_cd(t_params *data, t_node *pipe_line)
{
	char		current_path[PATH_MAX + 2];
	char		*target_path;
	t_minishell	*minishell;

	minishell = data->minishell;
	if (!getcwd(current_path, PATH_MAX + 1))
		return (BUILTIN_FAIL);
	target_path = create_target_path(minishell, pipe_line, current_path);
	if (!target_path)
	{
		if (errno)
		{
			print_error(pipe_line->arg[0], errno, pipe_line->arg[1]);
			errno = 0;
		}
		return (BUILTIN_FAIL);
	}
	return (chd(minishell, pipe_line, target_path, current_path));
}
