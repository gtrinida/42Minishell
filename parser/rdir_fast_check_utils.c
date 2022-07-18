/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_fast_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 02:34:10 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/19 02:46:48 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_utils(char *line, int i)
{
	if (line[i] == '|')
	{
		printf("minishel: syntax error near unexpected token `||'\n");
		return (0);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	check_after_rdir_pipe(char *line, int i, char *type)
{
	i++;
	if (type[0] == '>' && !type[1])
	{
		while (line[i])
		{
			if (!is_nothing(line[i]))
				return (1);
			i++;
		}
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else
	{	
		if (!pipe_utils(line, i))
			return (0);
	}
	return (1);
}

int	check_after_rdir_utils(char *line, int i)
{
	if (line[i + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (line[i + 1] == '>' && line[i + 2] == '>')
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		return (0);
	}
	if (line[i + 1] == '>')
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		return (0);
	}
	if (line[i + 1] == '<' && line[i + 2] == '<')
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (0);
	}
	return (1);
}

int	check_after_rdir_utils_sec(char *line, int i)
{
	if (line[i + 1] == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (0);
	}
	if (!line[i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	check_after_rdir(char *line, int i, char *type)
{
	if (line[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	i++;
	while (is_nothing(line[i]))
	{
		if (!check_after_rdir_utils(line, i))
			return (0);
		if (!check_after_rdir_utils_sec(line, i))
			return (0);
		i++;
	}
	if (line[i] == '|')
	{
		if (!check_after_rdir_pipe(line, i, type))
			return (0);
	}
	return (1);
}
