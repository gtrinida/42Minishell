/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:20:13 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/25 21:47:44 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list_utils(t_node *tmp, t_rdir *rdir)
{
	if (tmp->need_to_free_arg == 1)
	{
		free(tmp->arg);
		tmp->need_to_free_arg = 0;
		tmp->need_to_free_str = 0;
	}
	while (rdir != NULL)
	{
		tmp->rdir = rdir->next;
		if (rdir->arg)
		{
			free(rdir->arg);
		}
		free(rdir);
		rdir = tmp->rdir;
	}
	free(tmp);
}

void	clear_list(t_node **list)
{
	t_node	*tmp;
	t_rdir	*rdir;
	int		i;

	i = 0;
	tmp = *list;
	while (tmp != NULL)
	{
		*list = tmp->next;
		free(tmp->cmd);
		while (i < tmp->arg_count)
		{
			free(tmp->arg[i]);
			i++;
		}
		if (tmp->arg_count == 0 && tmp->need_to_free_str == 1)
			free(tmp->arg[0]);
		i = 0;
		rdir = tmp->rdir;
		clear_list_utils(tmp, rdir);
		tmp = *list;
	}
}
