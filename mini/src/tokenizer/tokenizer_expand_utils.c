/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expand_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:15 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:19:16 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tok_str_append_char(char *acc, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (ft_strjoin(acc, buf));
}

static int	append_part_inner(char **res, char *part)
{
	*res = ft_strjoin(*res, part);
	if (*res)
		return (0);
	else
		return (-1);
}

char	*tok_expand_inner(const char *s, t_env *env, t_shell *shell)
{
	int		k;
	char	*res;
	char	*part;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	k = 0;
	while (s[k])
	{
		if (s[k] == '$')
		{
			part = tok_handle_env(s, &k, env, shell);
			if (!part || append_part_inner(&res, part) == -1)
				return (NULL);
		}
		else
		{
			res = tok_str_append_char(res, s[k++]);
			if (!res)
				return (NULL);
		}
	}
	return (res);
}

char	*tok_env_value_for_key(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (env->value)
				return (ft_strdup(env->value));
			else
				return (ft_strdup(""));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

int	join_part(char **res, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(*res, part);
	*res = tmp;
	if (tmp)
		return (0);
	else
		return (-1);
}
