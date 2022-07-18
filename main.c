/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 05:41:02 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/23 05:41:03 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_params	*data;
	int			res;

	(void)argc;
	(void)argv;
	data = NULL;
	res = 0;
	if (init(&data, env))
		return (EXIT_FAILURE);
	sighandler_set(DEFAULT_MODE);
	cycle(data, res);
	return (EXIT_SUCCESS);
}
