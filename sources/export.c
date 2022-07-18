/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:05 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/26 02:39:53 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_new_val(t_minishell *minishell, t_node *pipe_line)
{
	int	i;
	int	err;

	i = 1;
	err = M_OK;
	while (pipe_line->arg[i])
	{
		if (i == 1 && pipe_line->arg[i][0] == '-' && pipe_line->arg[i][1])
		{
			print_error(pipe_line->arg[0], INVALID_IDENTIFER,
				pipe_line->arg[i]);
			return (BUILTIN_FAIL);
		}
		else if (envvar_validate_new(pipe_line->arg[i]))
		{
			err = M_ERR;
			print_error(pipe_line->arg[0], INVALID_IDENTIFER,
				pipe_line->arg[i]);
		}
		else if (envlist_add_var(minishell, pipe_line->arg))
			return (BUILTIN_FAIL);
		++i;
	}
	return (err);
}

int	ft_export(t_params *data, t_node *pipe_line)
{
	t_env_list	*ptr;

	if (pipe_line->arg[1])
		return (export_new_val(data->minishell, pipe_line));
	select_sort(data->minishell->env_list);
	ptr = data->minishell->env_list;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, "_") != 0)
		{
			if (ptr->val)
				printf("declare -x %s=\"%s\"\n", ptr->key, ptr->val);
			else
				printf("declare -x %s\n", ptr->key);
		}
		ptr = ptr->next;
	}
	return (M_OK);
}
