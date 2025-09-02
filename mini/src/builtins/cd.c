/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:15:50 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:15:52 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_home_path(t_env **env)
{
	t_env	*home;

	home = *env;
	while (home && ft_strcmp(home->key, "HOME") != 0)
		home = home->next;
	if (!home || !home->value)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (NULL);
	}
	return (home->value);
}

static void	update_env_vars(t_env **env, char *old_pwd, int have_old)
{
	char	new_pwd[PATH_MAX];
	t_env	*var;

	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		var = *env;
		while (var)
		{
			if (have_old && ft_strcmp(var->key, "OLDPWD") == 0)
				var->value = ft_strdup(old_pwd);
			else if (ft_strcmp(var->key, "PWD") == 0)
				var->value = ft_strdup(new_pwd);
			var = var->next;
		}
	}
}

int	builtin_cd(char **argv, t_env **env)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	int		have_old;

	have_old = (getcwd(old_pwd, sizeof(old_pwd)) != NULL);
	if (!argv[1])
	{
		path = get_home_path(env);
		if (!path)
			return (1);
	}
	else if (argv[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	else
		path = argv[1];
	if (chdir(path) == -1)
		return (perror("minishell: cdx"), 1);
	update_env_vars(env, old_pwd, have_old);
	return (0);
}
