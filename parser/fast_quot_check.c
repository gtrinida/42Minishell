/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_quot_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 00:48:43 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/19 01:40:47 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fast_singles_check(char *line, char *flag, int *i, int *counter_singles)
{
	int	i_tmp;

	i_tmp = *i;
	*flag = line[*i];
	*counter_singles += 1;
	while (line[*i])
	{
		(*i)++;
		if (line[*i] == *flag)
		{
			*counter_singles += 1;
			*flag = 0;
			break ;
		}
	}
	if (!even_or_odd(*counter_singles))
	{
		if (before_after(line, i_tmp, '\''))
			*counter_singles += 1;
		else
			return (-1);
	}
	return (i_tmp);
}

int	fast_double_check(char *line, char *flag, int *i, int *counter_double)
{
	int	i_tmp;

	i_tmp = *i;
	*flag = line[*i];
	*counter_double += 1;
	while (line[*i])
	{
		(*i)++;
		if (line[*i] == *flag)
		{
			*counter_double += 1;
			*flag = 0;
			break ;
		}
	}
	if (!even_or_odd(*counter_double))
	{
		if (before_after(line, i_tmp, '\"'))
			*counter_double += 1;
		else
			return (-1);
	}
	return (i_tmp);
}

int	res_quotes_check(int counter_double, int counter_singles)
{
	if (!even_or_odd(counter_double))
		return (0);
	if (!even_or_odd(counter_singles))
		return (0);
	return (1);
}

int	fast_quotes_check_utils(char *line, int i, int count_d, int count_s)
{
	char	flag;
	int		i_tmp;

	i_tmp = i;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !flag)
		{
			i_tmp = fast_double_check(line, &flag, &i, &count_d);
			if (i_tmp < 0)
				return (0);
		}
		if (line[i] == '\'' && !flag)
		{
			i_tmp = fast_singles_check(line, &flag, &i, &count_s);
			if (i_tmp < 0)
				return (0);
		}
		if (!line[i])
			return (1);
		i++;
	}
	return (res_quotes_check(count_d, count_s));
}

int	fast_quotes_check(char *line)
{
	int	i;
	int	counter_double;
	int	counter_singles;

	i = 0;
	counter_singles = 0;
	counter_double = 0;
	if (!fast_quotes_check_utils(line, i, counter_double, counter_singles))
		return (0);
	return (1);
}
