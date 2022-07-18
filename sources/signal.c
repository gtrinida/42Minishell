/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:25 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 03:20:52 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interactive_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 1;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	heredoc_sigint(int signal)
{
	if (signal == SIGINT)
		close(STDIN_FILENO);
}

static int	sethandler_sigquit(int mode)
{
	struct sigaction	sig_default;

	ft_memset(&sig_default, 0, sizeof(sig_default));
	if (mode == DEFAULT_MODE
		|| mode == HEREDOC_MODE
		|| mode == EXEC_MODE_PARENT)
		sig_default.sa_handler = SIG_IGN;
	else if (mode == EXEC_MODE_CHILD)
		sig_default.sa_handler = SIG_DFL;
	else
		return (M_ERR);
	return (sigaction(SIGQUIT, &sig_default, NULL));
}

static int	sethandler_sigint(int mode)
{
	struct sigaction	sig_default;

	ft_memset(&sig_default, 0, sizeof(sig_default));
	if (mode == DEFAULT_MODE)
		sig_default.sa_handler = interactive_sigint;
	else if (mode == HEREDOC_MODE)
		sig_default.sa_handler = heredoc_sigint;
	else if (mode == EXEC_MODE_PARENT)
		sig_default.sa_handler = SIG_IGN;
	else if (mode == EXEC_MODE_CHILD)
		sig_default.sa_handler = SIG_DFL;
	else
		return (M_ERR);
	return (sigaction(SIGINT, &sig_default, NULL));
}

int	sighandler_set(int mode)
{
	if (sethandler_sigint(mode) || sethandler_sigquit(mode))
		return (M_ERR);
	return (M_OK);
}
