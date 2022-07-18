/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 01:37:58 by ndillon           #+#    #+#             */
/*   Updated: 2022/06/19 01:37:58 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get_val(t_env_list *env_list, char *key)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, key))
			return (env_list->val);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		++i;
	}
	word = ft_substr(str, 0, i);
	return (word);
}

int	expand_var(t_minishell *minishell, char *line, int fd, int *i)
{
	char	*var;
	char	*env_val;

	if (line[*i + 1] == '?')
	{
		ft_putnbr_fd(g_status, fd);
		i += 2;
	}
	else
	{
		var = get_word(line + *i + 1);
		if (!var)
			return (M_ERR);
		env_val = env_get_val(minishell->env_list, var);
		if (env_val)
			write(fd, env_val, ft_strlen(env_val));
		*i += ft_strlen(var) + 1;
		free(var);
	}
	return (M_OK);
}

int	heredoc_put_str(t_minishell *minishell, char *line, int fd, int expand)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!expand && line[i] == '$' && line[i + 1])
		{
			if (expand_var(minishell, line, fd, &i))
				return (M_ERR);
		}
		else
			write(fd, &line[i++], 1);
	}
	write(fd, "\n", 1);
	return (M_OK);
}

char	*heredoc_fname(int index)
{
	char	*tmp;
	char	*fname;

	tmp = ft_itoa(index);
	if (!tmp)
		return (NULL);
	fname = ft_strjoin("./minishell_heredoc_", tmp);
	free(tmp);
	return (fname);
}
