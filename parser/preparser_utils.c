/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:10:48 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 22:46:59 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_len_of_command_utils(char *line, int i, char *flag)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!*flag)
			{
				*flag = line[i];
				i++;
			}
			if (*flag == line[i])
				*flag = 0;
		}
		if ((line[i] == ' ' || line[i] == '\t') && !*flag)
			return (i);
		i++;
	}
	return (i);
}

int	check_len_of_command(char *line, int i)
{
	char	flag;

	flag = 0;
	while (is_nothing(line[i]))
		i++;
	i = check_len_of_command_utils(line, i, &flag);
	if (flag)
	{
		printf("minishell: syntax error: unclosed quotes\n");
		return (-1);
	}
	return (i);
}

void	check_quotes_cycle_utils(char *line, t_quotes *quot,
	t_params *data, char **env)
{
	int	len;

	len = ft_strlen(line);
	if (len > quot->i)
	{
		if (!quot->flag && len > quot->i && (line[quot->i] == '\''
				|| line[quot->i] == '\"'))
			before_inside(quot, data, line, env);
	}
	if (len > quot->i)
	{	
		while (line[quot->i] && quot->flag)
			inside_quotes(line, quot, data, env);
	}
}

void	check_quotes_cycle(char *line, t_quotes *quot,
	t_params *data, char **env)
{
	int	len;

	len = ft_strlen(line);
	while (line[quot->i])
	{	
		if (len > quot->i)
			work_with_dollar_outside(line, quot, data, env);
		check_quotes_cycle_utils(line, quot, data, env);
		if (len > quot->i)
		{
			if (line[quot->i] != '\"' && line[quot->i] != '\'')
				not_quotes(line, quot, data);
		}
		if (line[quot->i - 1] == '\0')
			break ;
	}
}

void	check_quotes_utils(char *line, t_params *data, char **env)
{
	t_quotes	*quot;

	quot = malloc(sizeof(t_quotes));
	param_init(quot);
	while (is_nothing(line[quot->i]))
		quot->i++;
	check_quotes_cycle(line, quot, data, env);
	data->line[quot->j] = '\0';
	last_preparation(data, quot, 0, 0);
	free (data->line);
	free (quot);
}
