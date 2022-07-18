/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 20:53:22 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_join(t_params *data, t_quotes *quot, char *env_value)
{
	int	i;

	i = 0;
	while (env_value[i])
	{
		data->line[quot->j] = env_value[i];
		i++;
		quot->j++;
	}
}

void	is_it_env_utils(int *j, int start_tmp, int *start)
{
	*j = 0;
	*start = start_tmp;
}

int	is_it_env(char **env, char *line, int end, int start)
{
	int	i;
	int	j;
	int	start_tmp;

	start_tmp = start;
	i = 0;
	j = 0;
	while (env[i])
	{
		if (env[i][j] == line[start])
		{
			while (env[i][j] != '=' && start <= end && env[i][j] == line[start])
			{
				start++;
				j++;
			}
			if (env[i][j] == '=' && start == end + 1)
				return (1);
			else
				is_it_env_utils(&j, start_tmp, &start);
		}
		i++;
	}
	return (0);
}

void	get_new_memory(t_params *data, int len, t_quotes *quot)
{
	char	*tmp_line;
	int		i;

	i = 0;
	tmp_line = malloc(quot->j + 1);
	while (i < quot->j)
	{
		tmp_line[i] = data->line[i];
		i++;
	}
	tmp_line[i] = '\0';
	free(data->line);
	data->line = malloc(len + 1);
	i = 0;
	while (tmp_line[i])
	{
		data->line[i] = tmp_line[i];
		i++;
	}
	free(tmp_line);
}

int	get_env(t_params *data, t_quotes *quot, char *line, char **env)
{
	int		start;
	int		end;
	char	*env_value;
	char	*tmp_line;
	int		len;

	start = quot->i;
	end = get_finish(line, start);
	tmp_line = ft_substr(line, start, end - start + 1);
	env_value = get_value(tmp_line, env);
	len = quot->j + ft_strlen(env_value)
		+ ft_strlen(line) - (quot->i - (end - start));
	get_new_memory(data, len, quot);
	env_join(data, quot, env_value);
	free(env_value);
	free(tmp_line);
	quot->i = end + 1;
	return (1);
}
