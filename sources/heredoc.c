/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 04:01:07 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_readline(
	t_minishell *minishell,
	t_rdir *r_info,
	int fd)
{
	int		err;
	char	*line;

	while (1)
	{
		err = -1;
		line = readline(TERM_CYAN "> " TERM_RESET);
		if (!isatty(STDIN_FILENO))
			err = M_ERR;
		else if (!line || !ft_strcmp(line, r_info->arg))
			err = M_OK;
		else if (heredoc_put_str(minishell, line, fd, r_info->heredock_quote))
			err = M_ERR;
		safe_free(line);
		if (err == M_ERR || err == M_OK)
			return (err);
	}
}

char	*heredoc(t_minishell *minishell, t_rdir *r_info, int index)
{
	int		fd;
	char	*fname;

	fname = heredoc_fname(index);
	if (!fname)
		return (NULL);
	fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0 || heredoc_readline(minishell, r_info, fd))
	{
		safe_close(fd);
		unlink(fname);
		free(fname);
		fname = NULL;
	}
	return (fname);
}
