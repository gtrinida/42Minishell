/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir_fast_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:20:13 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/19 02:34:39 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_rdir_utils(char *line, int i)
{
	if (!is_rdir(line[i + 3]))
	{
		ft_putstr_fd("syntax error near unexpected token `", STDOUT_FILENO);
		ft_putchar_fd(line[i + 2], STDOUT_FILENO);
		ft_putendl_fd("'", STDOUT_FILENO);
		return ;
	}
	if (is_rdir(line[i + 3]))
	{
		if (line[i + 2] == line[i + 3])
		{
			ft_putstr_fd("syntax error near unexpected token `", STDOUT_FILENO);
			ft_putchar_fd(line[i + 2], STDOUT_FILENO);
			ft_putchar_fd(line[i + 3], STDOUT_FILENO);
			ft_putendl_fd("'", STDOUT_FILENO);
			return ;
		}
		else
		{
			ft_putstr_fd("syntax error near unexpected token `", STDOUT_FILENO);
			ft_putchar_fd(line[i + 2], STDOUT_FILENO);
			ft_putendl_fd("'", STDOUT_FILENO);
		}
	}		
}

int	double_rdir(char *line, int i)
{
	char	*type;

	if (is_rdir(line[i + 2]))
	{
		double_rdir_utils(line, i);
		return (0);
	}
	type = malloc(3);
	type[0] = line[i];
	type[1] = line[i + 1];
	type[2] = '\0';
	i++;
	if (!check_after_rdir(line, i, type))
	{
		free(type);
		return (0);
	}
	free(type);
	return (1);
}

int	single_rdir(char *line, int i)
{
	char	*type;

	type = malloc(2);
	type[0] = line[i];
	type[1] = '\0';
	if (!check_after_rdir(line, i, type))
	{
		free(type);
		return (0);
	}
	free(type);
	return (1);
}

int	rdir_bad_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] != '>')
			|| (line[i] == '<' && line[i + 1] != '<'))
		{
			if (!single_rdir(line, i))
				return (0);
		}
		if ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<'))
		{
			if (!double_rdir(line, i))
				return (0);
		}
		i++;
	}
	return (1);
}
