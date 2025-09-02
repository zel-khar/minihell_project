/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:08 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:19:09 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_env_value(t_env *env, const char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			else
				return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*expand_var(const char *str, int *i, t_env *env, int last_status)
{
	int		start;
	int		len;
	char	*key;

	start = *i;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_status));
	}
	while (str[*i] && (str[*i] == '_' || (str[*i] >= 'A' && str[*i] <= 'Z')
			|| (str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= '0'
				&& str[*i] <= '9')))
		(*i)++;
	len = *i - start - 1;
	key = ft_strndup(str + start + 1, len);
	return (find_env_value(env, key));
}

static char	*append_char(char *acc, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (ft_strjoin(acc, buf));
}

static int	process_expansion_char(const char *line, int *i, char **res,
		t_shell *shell)
{
	char	*part;

	if (line[*i] == '$')
	{
		part = expand_var(line, i, shell->env_list, shell->exit_status);
		if (!part)
			return (0);
		*res = ft_strjoin(*res, part);
		if (!*res)
			return (0);
	}
	else
	{
		*res = append_char(*res, line[(*i)++]);
		if (!*res)
			return (0);
	}
	return (1);
}

char	*expand_line(const char *line, t_shell *shell)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (line[i])
	{
		if (!process_expansion_char(line, &i, &res, shell))
			return (NULL);
	}
	return (res);
}
