/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:58:23 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 06:06:55 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_list_clear(t_minishell *minishell)
{
	t_env_list	*ptr;

	ptr = minishell->env_list;
	while (ptr)
	{
		minishell->env_list = minishell->env_list->next;
		env_del_elem(ptr);
		ptr = minishell->env_list;
	}
}

void	env_del_elem(t_env_list *env_list)
{
	free(env_list->key);
	if (env_list->val)
		free(env_list->val);
	free(env_list);
}

void	envlist_delone(t_minishell *minishell, char *key)
{
	t_env_list	*ptr;
	t_env_list	*tmp;

	if (!minishell->env_list)
		return ;
	if (!ft_strcmp(minishell->env_list->key, key))
	{
		tmp = minishell->env_list;
		minishell->env_list = minishell->env_list->next;
		env_del_elem(tmp);
	}
	else
	{
		ptr = minishell->env_list;
		while (ptr && ptr->next)
		{
			if (!ft_strcmp(ptr->next->key, key))
			{
				tmp = ptr->next;
				ptr->next = ptr->next->next;
				env_del_elem(tmp);
			}
			ptr = ptr->next;
		}
	}
}

int	envlist_add_var(t_minishell *minishell, char **argv)
{
	int			i;
	t_env_list	*elem;

	i = 1;
	while (argv[i])
	{
		elem = new_env_elem(argv[i]);
		if (!elem)
		{
			env_list_clear(minishell);
			return (errno);
		}
		else
			env_add_back(&minishell->env_list, elem);
		++i;
	}
	return (M_OK);
}

void	env_add_back(t_env_list **env_list, t_env_list *new_elem)
{
	t_env_list	*ptr;

	if (!*env_list)
	{
		*env_list = new_elem;
		return ;
	}
	ptr = *env_list;
	while (ptr->next && ft_strcmp(ptr->key, new_elem->key))
		ptr = ptr->next;
	if (!ft_strcmp(ptr->key, new_elem->key))
	{
		if (new_elem->val)
			envlist_change_val(*env_list, ptr->key, new_elem->val);
		free(new_elem->key);
		free(new_elem);
	}
	else
		ptr->next = new_elem;
}
