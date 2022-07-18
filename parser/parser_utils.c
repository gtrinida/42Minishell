/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:37:53 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 05:27:47 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_specsym(char sym)
{
	if ((sym < 48 || sym > 57) && !is_nothing(sym) && sym != '\0')
		return (1);
	return (0);
}

int	is_it_letter(char sym)
{
	if ((sym >= 97 && sym <= 122) || (sym >= 65 && sym <= 90))
		return (1);
	return (0);
}

int	even_or_odd(int dight)
{
	if (dight % 2 == 0)
		return (1);
	else
		return (0);
}

int	is_nothing(char sym)
{
	if (sym == ' ' || sym == '\t')
		return (1);
	return (0);
}
