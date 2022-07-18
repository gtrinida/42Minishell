/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 00:41:49 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 23:38:56 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	we_need_this_quotes(char *line, int i, char flag)
{
	char	anti_flag;

	if (flag == '\'')
		anti_flag = '\"';
	if (flag == '\"')
		anti_flag = '\'';
	if (line[i])
		i++;
	while (line[i])
	{
		if (line[i] == flag)
			return (0);
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '$'
			|| line[i] == '>' || line[i] == '<'
			|| line[i] == anti_flag)
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes(char *line, t_params *data, char **env)
{
	int	end;

	end = 0;
	data->line = malloc(sizeof(char) * ft_strlen(line) + 2);
	end = check_len_of_command(line, 0);
	if (end < 0)
	{
		free(data->line);
		return (0);
	}
	check_quotes_utils(line, data, env);
	return (1);
}

void	get_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\f')
			line[i] = '|';
		i++;
	}
	return ;
}

int	parser_utils(t_params *data, char *line, char **env)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, '|');
	while (split[i])
	{
		get_pipe(split[i]);
		data->key = 1;
		check_dollar(split[i], 0, 0, 0);
		if (!check_quotes(split[i], data, env))
			return (0);
		free(split[i]);
		i++;
	}
	free (split);
	return (1);
}

int	parser(char *line, char **env, t_params *data)
{
	int			pipe;

	if (!rdir_bad_syntax(line))
		return (0);
	pipe = pipe_bad_syntax(line);
	if (!pipe)
		return (0);
	data->key = 1;
	if (pipe > 1)
	{
		if (!parser_utils(data, line, env))
			return (0);
		return (1);
	}
	get_pipe(line);
	check_dollar(line, 0, 0, 0);
	if (!check_quotes(line, data, env))
		return (0);
	return (1);
}
