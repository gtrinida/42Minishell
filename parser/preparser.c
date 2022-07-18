/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 23:40:57 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredock_behind(char *line, int i)
{
	if (i == 0)
		return (0);
	i--;
	while (is_nothing(line[i]))
			i--;
	if (line[i] == '<')
	{
		if (i == 0)
			return (0);
		if (line[i - 1] == '<')
			return (1);
	}
	return (0);
}

void	data_init(t_params *data)
{
	data->list = NULL;
	data->key = 1;
}

void	start_cmd_line(t_params *data, char *line, int *res)
{
	if (!fast_quotes_check(line))
	{
		printf("minishell: syntax error: unclosed quotes\n");
		*res = 0;
		exec_pipe_line(data);
		return ;
	}
	else if (parser(line, data->minishell->env_arr, data))
	{
		*res = 1;
		if (line)
			free(line);
		exec_pipe_line(data);
		clear_list(&(data->list));
	}
	else
		*res = 0;
}

int	cycle(t_params *data, int res)
{
	char	*line;

	while (1)
	{
		line = readline("minishell-3.2$ ");
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit_minishell(data, g_status);
		}
		if (*line)
		{
			put_history_line(line, data->minishell->history_fd);
			env_to_array(data->minishell);
			start_cmd_line(data, line, &res);
			if (!res)
				free(line);
			res = 0;
		}
		else
			free(line);
	}
	return (M_OK);
}
