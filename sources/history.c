/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:13:14 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:50:36 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_history_file(char *home_path)
{
	int		fd;
	char	*history_file;

	history_file = ft_strjoin(home_path, "/.minishell_history");
	if (!history_file)
		return (-1);
	fd = open((const char *)history_file,
			O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	free(history_file);
	return (fd);
}

void	ft_read_history(int fd)
{
	char	*line;
	char	*temp;

	while (1)
	{
		temp = get_next_line(fd);
		line = ft_strtrim(temp, "\n");
		free(temp);
		if (!line)
			break ;
		add_history(line);
		free(line);
	}
}

int	put_history_line(char *line, int fd)
{
	int	err;

	add_history(line);
	if (fd <= 0)
		return (M_OK);
	err = write(fd, line, ft_strlen(line));
	if (err < 0)
		return (M_ERR);
	err = write(fd, "\n", 1);
	return (err);
}
