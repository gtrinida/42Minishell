/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_backup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:28 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 01:22:25 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stdbackup_copy(t_std_backup *std_backup)
{
	errno = 0;
	std_backup->stdin_backup = dup(STDIN_FILENO);
	if (std_backup->stdin_backup >= 0)
	{
		std_backup->stdout_backup = dup(STDIN_FILENO);
		if (std_backup->stdout_backup >= 0)
		{
			std_backup->stderr_backup = dup(STDIN_FILENO);
			if (std_backup->stderr_backup < 0)
			{
				close(std_backup->stdin_backup);
				close(std_backup->stdout_backup);
			}
		}
		else
			close(std_backup->stdin_backup);
	}
	return (errno);
}

int	stdbackup_set(t_std_backup *std_backup)
{
	if (dup2(std_backup->stdin_backup, STDIN_FILENO) < 0
		|| dup2(std_backup->stdout_backup, STDOUT_FILENO) < 0
		|| dup2(std_backup->stderr_backup, STDERR_FILENO) < 0)
		return (M_ERR);
	return (M_OK);
}

int	stdbackup_close(t_std_backup *std_backup)
{
	if (safe_close(std_backup->stdin_backup)
		|| safe_close(std_backup->stdout_backup)
		|| safe_close(std_backup->stderr_backup))
		return (M_ERR);
	return (M_OK);
}
