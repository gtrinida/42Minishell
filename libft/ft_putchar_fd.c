/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 00:37:02 by ndillon           #+#    #+#             */
/*   Updated: 2021/10/12 00:37:02 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
