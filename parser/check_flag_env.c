/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/21 20:14:49 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker(const char *tmp_line, char *env_name)
{
	int	result;

	result = (env_name && ft_strlen(tmp_line) == ft_strlen(env_name)
			&& ft_strncmp(tmp_line, env_name, ft_strlen(tmp_line)) == 0);
	free(env_name);
	return (result);
}

char	*get_value(char *tmp_line, char **env)
{
	int		i;
	int		j;
	char	*env_name;
	char	*env_value;

	i = -1;
	env_value = 0;
	while (env[++i])
	{
		env_name = 0;
		j = 0;
		if (ft_strnstr(env[i], tmp_line, ft_strlen(tmp_line)))
		{
			while (env[i][j] != '=')
				j++;
			env_name = ft_substr(env[i], 0, j);
		}
		if (checker(tmp_line, env_name))
			env_value = ft_strdup(&env[i][j + 1]);
		if (env_value)
			break ;
	}
	if (!env_value)
		env_value = ft_strdup(" ");
	return (env_value);
}

void	write_one_sym(t_params *data, t_quotes *quot, char *line)
{
	data->line[quot->j] = line[quot->i];
	quot->j++;
	quot->i++;
}

void	check_flag(t_params *data, t_quotes *quot, char *line)
{
	if (!quot->flag)
	{
		while (line[quot->i] != '$')
		{
			if (line[quot->i] == quot->flag)
				quot->flag = 0;
			write_one_sym(data, quot, line);
		}
	}
	if (quot->flag)
	{
		while (line[quot->i] && quot->flag)
		{
			if (line[quot->i] == '$' && is_nothing(line[quot->i - 1])
				&& !is_nothing(line[quot->i + 1]))
				return ;
			if (line[quot->i] == quot->flag)
				quot->flag = 0;
			write_one_sym(data, quot, line);
			if (is_nothing(line[quot->i]) && line[quot->i + 1] == '$')
				write_one_sym(data, quot, line);
		}
	}
}
