/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:35 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 06:05:47 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
init builtin array for t_minishell struct 
*/
void	builtin_arr_init(t_minishell *minishell)
{
	minishell->built_in[BIN_ECHO] = ft_echo;
	minishell->built_in[BIN_CD] = ft_cd;
	minishell->built_in[BIN_PWD] = ft_pwd;
	minishell->built_in[BIN_EXPORT] = ft_export;
	minishell->built_in[BIN_UNSET] = ft_unset;
	minishell->built_in[BIN_ENV] = ft_env;
	minishell->built_in[BIN_EXIT] = ft_exit;
}

int	is_builtin(char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return (BIN_ECHO);
	if (!strcmp(cmd, "cd"))
		return (BIN_CD);
	if (!strcmp(cmd, "pwd"))
		return (BIN_PWD);
	if (!strcmp(cmd, "export"))
		return (BIN_EXPORT);
	if (!strcmp(cmd, "unset"))
		return (BIN_UNSET);
	if (!strcmp(cmd, "env"))
		return (BIN_ENV);
	if (!strcmp(cmd, "exit"))
		return (BIN_EXIT);
	return (-1);
}

static int	check_overflow_util(char *s, long long int i, int flag)
{
	if (!*(s + 1))
		return (M_OK);
	if (*(s + 2))
		return (M_ERR);
	if (i > LLONG_MAX / 10)
		return (M_ERR);
	if (i == LLONG_MAX / 10 && *(s + 1) - 48 > 8 && flag)
		return (M_ERR);
	if (i == LLONG_MAX / 10 && *(s + 1) - 48 > 7 && !flag)
		return (M_ERR);
	return (M_OK);
}

/*
check is number in passed string out of LLong int range
*/
int	check_overflow(char *s)
{
	long long int	i;
	int				num_len;
	int				flag;

	flag = 0;
	while (ft_isspace(*s))
		++s;
	if (*s == '-')
	{
		flag = 1;
		++s;
	}
	num_len = 0;
	while (*s)
	{
		i = i + (*s - 48);
		if (num_len == 17)
			return (check_overflow_util(s, i, flag));
		i *= 10;
		++num_len;
		++s;
	}
	return (M_OK);
}

int	env_len(t_env_list *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		if (ptr->val)
			i++;
		ptr = ptr->next;
	}
	return (i);
}
