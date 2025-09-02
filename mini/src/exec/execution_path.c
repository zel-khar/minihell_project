/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:08 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:47:22 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*search_in_paths(char **paths, const char *cmd)
{
	char		*dir;
	char		*full;
	int			i;
	struct stat	st;

	i = 0;
	while (paths && paths[i])
	{
		if (paths[i][0] == '\0')
			dir = ft_strjoin(".", "/");
		else
			dir = ft_strjoin(paths[i], "/");
		full = ft_strjoin(dir, cmd);
		if (stat(full, &st) == 0 && S_ISDIR(st.st_mode))
		{
			i++;
			continue ;
		}
		if (access(full, X_OK) == 0)
			return (full);
		i++;
	}
	return (NULL);
}

static const char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (env->value)
				return (env->value);
			else
				return ("");
		}
		env = env->next;
	}
	return (NULL);
}

/* split_path_preserve_empty is implemented in execution_path_utils.c */

char	*find_path(char *cmd, t_env *env)
{
	const char	*path;
	char		**paths;
	char		*full;
	int			idx;

	if (!cmd || cmd[0] == '\0')
		return (ft_strdup(cmd));
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (NULL);
	idx = 0;
	while (cmd[idx] && cmd[idx] != '/')
		idx++;
	if (cmd[idx] == '/')
		return (ft_strdup(cmd));
	path = env_get(env, "PATH");
	if (!path || path[0] == '\0')
		paths = split_path_preserve_empty(".");
	else
		paths = split_path_preserve_empty(path);
	full = search_in_paths(paths, cmd);
	return (full);
}
