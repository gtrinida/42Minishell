/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 02:07:25 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 02:07:35 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_copy(t_minishell *minishell, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		++i;
	minishell->env_arr = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		minishell->env_arr[i] = ft_strdup(env[i]);
		if (!minishell->env_arr[i])
		{
			while (--i >= 0)
				free(minishell->env_arr[i]);
			free(minishell->env_arr);
			return (M_ERR);
		}
		++i;
	}
	minishell->env_arr[i] = NULL;
	return (M_OK);
}
