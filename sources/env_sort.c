/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:12:42 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 01:16:17 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	select_sort_util(t_env_list *ptr, t_env_list *j, t_env_list *pos)
{
	char	*temp_key;
	char	*temp_val;

	while (ptr->next)
	{
		pos = ptr;
		temp_key = ptr->key;
		temp_val = ptr->val;
		j = ptr->next;
		while (j)
		{
			if (ft_strcmp(j->key, temp_key) < 0)
			{
				pos = j;
				temp_key = j->key;
				temp_val = j->val;
			}
			j = j->next;
		}
		pos->key = ptr->key;
		pos->val = ptr->val;
		ptr->key = temp_key;
		ptr->val = temp_val;
		ptr = ptr->next;
	}
}

void	select_sort(t_env_list *ptr)
{
	t_env_list	*j;
	t_env_list	*pos;

	if (!ptr)
		return ;
	j = NULL;
	pos = NULL;
	select_sort_util(ptr, j, pos);
}
