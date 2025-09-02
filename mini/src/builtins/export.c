/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:20 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:41:58 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	set_or_add_env(t_env **env, const char *key, const char *val,
		int append)
{
	t_env	*var;

	var = find_env(*env, key);
	if (var)
		update_existing_env(var, val, append);
	else
		create_new_env(env, key, val);
}

static char	*find_equals_sign(const char *arg)
{
	int	k;

	k = 0;
	while (arg[k])
	{
		if (arg[k] == '=')
			return ((char *)(arg + k));
		k++;
	}
	return (NULL);
}

static char	*extract_key(const char *arg, char *eq, int *append)
{
	*append = 0;
	if (eq && eq > arg && *(eq - 1) == '+')
	{
		*append = 1;
		return (ft_strndup(arg, (eq - arg) - 1));
	}
	else if (eq)
		return (ft_strndup(arg, eq - arg));
	else
		return (ft_strdup(arg));
}

static int	export_one(const char *arg, t_env **env)
{
	char	*eq;
	char	*key;
	int		append;

	eq = find_equals_sign(arg);
	key = extract_key(arg, eq, &append);
	if (!key)
		return (1);
	if (!is_valid_var_name(key))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	if (eq)
		set_or_add_env(env, key, eq + 1, append);
	else
		set_or_add_env(env, key, NULL, 0);
	return (0);
}

int	builtin_export(char **argv, t_env **env)
{
	int	status;
	int	i;

	if (!argv[1])
		return (display_exports(*env), 0);
	status = 0;
	i = 1;
	while (argv[i])
	{
		status |= export_one(argv[i], env);
		i++;
	}
	return (status);
}
