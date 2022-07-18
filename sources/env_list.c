/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:39 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/26 02:30:20 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_create_line(t_env_list *ptr)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(ptr->key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, ptr->val);
	free(temp);
	return (result);
}

int	env_fill_array(t_minishell *minishell)
{
	int			i;
	t_env_list	*ptr;

	ptr = minishell->env_list;
	i = 0;
	while (ptr)
	{
		if (ptr->val)
		{
			minishell->env_arr[i] = env_create_line(ptr);
			if (!minishell->env_arr[i])
			{
				while (--i >= 0)
					free(minishell->env_arr[i]);
				return (M_ERR);
			}
			++i;
		}
		ptr = ptr->next;
	}
	minishell->env_arr[i] = NULL;
	return (0);
}

int	env_to_array(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->env_arr)
	{
		while (minishell->env_arr[i])
			free(minishell->env_arr[i++]);
		free(minishell->env_arr);
	}
	minishell->env_arr = (char **)
		malloc((env_len(minishell->env_list) + 1) * sizeof(char *));
	if (!minishell->env_arr)
		return (errno);
	if (!env_len(minishell->env_list))
	{
		minishell->env_arr[0] = NULL;
		return (M_OK);
	}
	if (env_fill_array(minishell))
	{
		minishell->env_arr = NULL;
		return (M_ERR);
	}
	return (M_OK);
}

static int	fill_list(t_minishell *minishell, char **envp)
{
	int			i;
	t_env_list	*ptr;

	i = 0;
	ptr = new_env_elem(envp[i]);
	if (!ptr)
		return (errno);
	minishell->env_list = ptr;
	++i;
	while (envp[i])
	{
		ptr->next = new_env_elem(envp[i]);
		if (!ptr->next)
		{
			env_list_clear(minishell);
			return (errno);
		}
		ptr = ptr->next;
		++i;
	}
	ptr->next = NULL;
	return (M_OK);
}

int	env_to_list(t_minishell *minishell, char **envp)
{
	minishell->env_list = NULL;
	minishell->env_list_size = 0;
	if (!envp[0])
		return (M_OK);
	return (fill_list(minishell, envp));
}
