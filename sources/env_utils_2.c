/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:46 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 04:30:53 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envlist_change_val(t_env_list *env_list, char *key, char *new_val)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, key))
			return (env_set_val(env_list, new_val));
		env_list = env_list->next;
	}
	free(new_val);
	return (M_OK);
}

int	envarr_change_val(char **env, char *key, char *val)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(env[i], key))
		{
			free(env[i]);
			tmp = ft_strjoin(key, "=");
			if (!tmp)
				return (M_ERR);
			env[i] = ft_strjoin(tmp, val);
			free(tmp);
			if (!env[i])
				return (M_ERR);
			return (M_OK);
		}
		++i;
	}
	return (M_ERR);
}

char	*ft_getenv(t_env_list *env_list, char *name)
{
	while (env_list && ft_strcmp(env_list->key, name))
		env_list = env_list->next;
	if (!env_list)
		return (NULL);
	return (env_list->val);
}

int	envvar_validate(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (M_ERR);
	++i;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (M_ERR);
		++i;
	}
	return (M_OK);
}

int	envvar_validate_new(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (M_ERR);
	++i;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (M_ERR);
		++i;
	}
	return (M_OK);
}
