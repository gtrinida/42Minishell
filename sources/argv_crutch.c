/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_crutch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 05:55:42 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:55:43 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_args(char **fixed, char **argv, int i, int n_arg)
{
	while (i < n_arg)
	{
		fixed[i + 1] = ft_strdup(argv[i]);
		if (!fixed[i + 1])
		{
			while (i >= 0)
				free(fixed[i--]);
			free(fixed);
			return (M_ERR);
		}
		++i;
	}
	fixed[i + 1] = NULL;
	return (M_OK);
}

char	**argv_crutch(char **argv, char *cmd, int n_arg)
{
	int		i;
	char	**fixed;

	i = 0;
	fixed = (char **)malloc((n_arg + 2) * sizeof(char *));
	if (!fixed)
		return (NULL);
	fixed[i] = ft_strdup(cmd);
	if (!fixed[i])
	{
		free(fixed);
		return (NULL);
	}
	if (fill_args(fixed, argv, i, n_arg))
		return (NULL);
	free_str_arr(argv, n_arg);
	return (fixed);
}
