/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:22:18 by ndillon           #+#    #+#             */
/*   Updated: 2021/12/22 16:22:20 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_tail(char *tail)
{
	char	*new_tail;
	char	*start;

	if (!tail)
		return (NULL);
	start = ft_strchr(tail, '\n');
	if (start == NULL || !start[1])
	{
		free(tail);
		return (NULL);
	}
	new_tail = ft_strdup(start + 1);
	free(tail);
	return (new_tail);
}

static char	*get_line(const char *tail)
{
	char	*line;
	int		size;

	size = 0;
	while (tail[size] != '\n' && tail[size])
		size++;
	if (tail[size] == '\n')
		line = (char *)malloc(size + 2);
	else
		line = (char *)malloc(size + 1);
	if (!line)
		return (NULL);
	if (tail[size] == '\n')
		line[size + 1] = '\0';
	while (size != -1)
	{
		line[size] = tail[size];
		size--;
	}
	return (line);
}

static char	*get_str(char *tail, int fd)
{
	char	*buff;
	char	*temp;
	int		readed;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = 1;
	while (!ft_strchr(tail, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed < 0 || (readed == 0 && tail[0] == '\0'))
		{
			free(tail);
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		temp = ft_strjoin(tail, buff);
		free(tail);
		tail = temp;
	}
	free(buff);
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tail)
	{
		tail = (char *)malloc(1);
		tail[0] = '\0';
	}
	tail = get_str(tail, fd);
	if (!tail)
		return (NULL);
	line = get_line(tail);
	tail = get_tail(tail);
	return (line);
}
