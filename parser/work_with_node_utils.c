/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_node_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:20:13 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 03:27:11 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdir	*create_node(int i)
{
	t_rdir	*node;

	(void)i;
	node = malloc(sizeof(t_rdir));
	node->next = NULL;
	node->type = -1;
	node->heredock_quote = 0;
	return (node);
}

void	add_rdir(t_rdir **rdir)
{
	t_rdir	*tmp;

	if (!*rdir)
	{
		*rdir = create_node(1);
		return ;
	}
	tmp = *rdir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_node(1);
}

t_node	*add_node(t_node **list, t_node *node)
{
	t_node	*tmp;

	if (*list == NULL)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
	return (node);
}
