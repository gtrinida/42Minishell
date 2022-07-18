/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defenv_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:34 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 06:03:14 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pwd(t_minishell *minishell)
{
	char		*path;
	char		*pwd;
	t_env_list	*pwd_var;

	path = (char *)malloc((PATH_MAX + 1) * sizeof(char));
	if (getcwd(path, PATH_MAX + 1) == NULL)
	{
		free(path);
		return (M_ERR);
	}
	if (ft_getenv(minishell->env_list, "PWD") == NULL)
	{
		pwd = ft_strjoin("PWD=", path);
		free(path);
		if (!pwd)
			return (M_ERR);
		pwd_var = new_env_elem(pwd);
		free(pwd);
		if (!pwd_var)
			return (M_ERR);
		env_add_back(&minishell->env_list, pwd_var);
	}
	else
		return (envlist_change_val(minishell->env_list, "PWD", path));
	return (M_OK);
}

static int	set_shlvl(t_minishell *minishell)
{
	char		*lvl;
	char		*shlvl;
	t_env_list	*shlvl_var;

	lvl = ft_getenv(minishell->env_list, "SHLVL");
	if (lvl == NULL)
		shlvl = ft_strdup("SHLVL=1");
	else
	{
		lvl = ft_itoa(ft_atoi(lvl) + 1);
		if (!lvl)
			return (M_ERR);
		shlvl = ft_strjoin("SHLVL=", lvl);
		free(lvl);
	}
	if (!shlvl)
		return (M_ERR);
	shlvl_var = new_env_elem(shlvl);
	free(shlvl);
	if (!shlvl_var)
		return (M_ERR);
	env_add_back(&minishell->env_list, shlvl_var);
	return (M_OK);
}

static int	set_underscore(t_minishell *minishell)
{
	t_env_list	*underscore_var;

	if (ft_getenv(minishell->env_list, "_"))
		return (M_OK);
	underscore_var = new_env_elem("_=⚣minishell⚣");
	if (!underscore_var)
		return (M_ERR);
	env_add_back(&minishell->env_list, underscore_var);
	return (M_OK);
}

static int	set_oldpwd(t_minishell *minishell)
{
	t_env_list	*oldpwd_var;

	if (ft_getenv(minishell->env_list, "OLDPWD"))
		return (envlist_change_val(minishell->env_list, "OLDPWD", NULL));
	oldpwd_var = new_env_elem("OLDPWD");
	if (!oldpwd_var)
		return (M_ERR);
	env_add_back(&minishell->env_list, oldpwd_var);
	return (M_OK);
}

int	default_env(t_minishell *minishell)
{
	if (set_pwd(minishell))
		return (M_ERR);
	if (set_shlvl(minishell))
		return (M_ERR);
	if (set_underscore(minishell))
		return (M_ERR);
	if (set_oldpwd(minishell))
		return (M_ERR);
	return (M_OK);
}
