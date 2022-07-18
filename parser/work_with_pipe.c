/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:10:48 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/20 07:40:26 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	on_pipe(char *line, int *i, int *correct_close)
{
	if (line[*i] == '\0')
	{
		printf("minishel: syntax error\n");
		return (0);
	}
	while (line[*i])
	{
		if (!is_nothing(line[*i]) && line[*i] != '|')
		{
			*correct_close = 1;
			break ;
		}
		if (line[*i] == '|')
		{
			printf("minishel: syntax error near unexpected token `|'\n");
			return (0);
		}
		(*i)++;
	}
	if (!(*correct_close))
	{
		printf("minishel: syntax error\n");
		return (0);
	}
	return (1);
}

int	check_bad_syntax_utils(char *line, char *flag, int *first, int *i)
{
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		if (!(*flag))
			*flag = line[*i];
		else if (*flag == line[*i])
			*flag = 0;
	}
	if (!is_nothing(line[*i]) && line[*i] == '|' && !(*first))
	{
		printf("minishel: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (!is_nothing(line[*i]) && line[*i] != '|')
		*first = 1;
	return (1);
}

int	check_bad_syntax(char *line, int i, int first, int pipe)
{
	char	flag;
	int		correct_close;

	flag = 0;
	correct_close = 0;
	while (line[i])
	{
		if (!check_bad_syntax_utils(line, &flag, &first, &i))
			return (0);
		if (line[i] == '|' && !flag)
		{
			pipe += 1;
			i++;
			if (!on_pipe(line, &i, &correct_close))
				return (0);
		}
		else if (line[i] == '|' && flag)
			line[i] = '\f';
		if (line[i])
			i++;
	}
	return (pipe);
}

int	pipe_bad_syntax(char *line)
{
	int	tmp;

	tmp = check_bad_syntax(line, 0, 0, 1);
	if (!tmp)
		return (0);
	if (tmp > 1)
		return (2);
	return (1);
}
