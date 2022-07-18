/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:56:45 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:50:11 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell *minishell)
{
	if (minishell->env_arr)
		free_strarr_terminated(minishell->env_arr);
	if (minishell->env_list)
		env_list_clear(minishell);
	safe_close(minishell->history_fd);
	free(minishell);
}

void	redirect_clear(t_node *node)
{
	t_rdir	*rdir;

	while (node)
	{
		rdir = node->rdir;
		while (rdir)
		{
			if (rdir->type == REDIRECT_HEREDOC)
			{
				if (rdir->fname)
				{
					if (unlink(rdir->fname))
					{
						ft_putendl_fd(ft_strerr(errno), STDERR_FILENO);
						ft_putendl_fd(rdir->fname, 1);
					}
					free(rdir->fname);
				}
			}
			rdir = rdir->next;
		}
		node = node->next;
	}
}
