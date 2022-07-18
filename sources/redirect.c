/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:22 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:46:33 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_rdir(t_minishell *minishell, t_rdir *redirect, int index)
{
	if (redirect->type == REDIRECT_HEREDOC)
	{
		redirect->fname = heredoc(minishell, redirect, index);
		if (!redirect->fname)
			return (HEREDOC_ERR);
		redirect->fd = open(redirect->fname, O_RDONLY);
	}
	else if (redirect->type == REDIRECT_IN)
		redirect->fd = open(redirect->arg, O_RDONLY);
	else if (redirect->type == REDIRECT_OUT)
		redirect->fd = open(redirect->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == REDIRECT_OUT_APPEND)
		redirect->fd = open(redirect->arg,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (M_OK);
}

int	make_redirect_s(t_minishell *minishell, t_rdir *redirect, int index)
{
	int	err;

	if (!redirect)
		return (M_OK);
	while (redirect)
	{
		err = open_rdir(minishell, redirect, index);
		if (err == HEREDOC_ERR)
			return (err);
		if (err == M_ERR || errno)
			return (M_ERR);
		redirect = redirect->next;
	}
	return (M_OK);
}

int	cmd_redirect_s(t_rdir *redirect)
{
	if (!redirect)
		return (M_OK);
	while (redirect)
	{
		if (redirect->type == REDIRECT_IN || redirect->type == REDIRECT_HEREDOC)
		{
			if (dup2(redirect->fd, STDIN_FILENO) < 0)
				return (M_ERR);
		}
		else if (redirect->type == REDIRECT_OUT
			|| redirect->type == REDIRECT_OUT_APPEND)
		{
			if (dup2(redirect->fd, STDOUT_FILENO) < 0)
				return (M_ERR);
		}
		if (close(redirect->fd))
			return (M_ERR);
		redirect = redirect->next;
	}
	return (M_OK);
}

int	cmd_redirect_close(t_rdir *redirect)
{
	int	i;

	i = 0;
	if (!redirect)
		return (M_OK);
	while (redirect)
	{
		if (safe_close(redirect->fd))
			return (M_ERR);
		redirect->fd = -1;
		redirect = redirect->next;
	}
	return (M_OK);
}

int	pipeline_set_fd(t_minishell *minishell, t_node *pipe_line)
{
	int	index;
	int	err;

	index = 0;
	while (pipe_line)
	{
		if (sighandler_set(HEREDOC_MODE))
			return (M_ERR);
		err = make_redirect_s(minishell, pipe_line->rdir, index);
		if (err)
			return (err);
		if (sighandler_set(DEFAULT_MODE))
			return (M_ERR);
		pipe_line = pipe_line->next;
		++index;
	}
	return (M_OK);
}
