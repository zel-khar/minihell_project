/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:16:22 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:16:33 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	**create_env_array(t_env *env, int n)
{
	t_env	**arr;
	int		i;

	arr = (t_env **)ft_malloc(sizeof(t_env *) * n);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

void	print_env_export(t_env *var)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(var->key, 1);
	if (var->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(var->value, 1);
		ft_putchar_fd('\"', 1);
	}
	ft_putchar_fd('\n', 1);
}

void	display_exports(t_env *env)
{
	int		n;
	t_env	**arr;
	int		i;

	n = count_env(env);
	if (n == 0)
		return ;
	arr = create_env_array(env, n);
	sort_env_ptrs(arr, n);
	i = 0;
	while (i < n)
	{
		print_env_export(arr[i]);
		i++;
	}
}

void	update_existing_env(t_env *var, const char *val, int append)
{
	char	*joined;

	if (append && val)
	{
		if (var->value)
		{
			joined = ft_strjoin(var->value, val);
			var->value = joined;
		}
		else
			var->value = ft_strdup(val);
	}
	else
	{
		if (val)
			var->value = ft_strdup(val);
		else
			var->value = NULL;
	}
}

void	create_new_env(t_env **env, const char *key, const char *val)
{
	t_env	*var;

	var = (t_env *)ft_malloc(sizeof(t_env));
	if (!var)
		return ;
	var->key = ft_strdup(key);
	if (val)
		var->value = ft_strdup(val);
	else
		var->value = NULL;
	var->next = *env;
	*env = var;
}
