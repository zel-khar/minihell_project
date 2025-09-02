/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:41 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:17:42 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*make_env_node(const char *entry)
{
	t_env	*new;
	char	*eq;

	new = (t_env *)ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = find_equals_in_entry(entry);
	set_env_key_value(new, entry, eq);
	new->next = NULL;
	return (new);
}

/* Copy environment to linked list */
t_env	*copy_env(char **envp)
{
	t_env	*head;
	t_env	*prev;
	int		i;
	t_env	*node;

	head = NULL;
	prev = NULL;
	i = 0;
	while (envp[i])
	{
		node = make_env_node(envp[i]);
		if (!node)
			return (NULL);
		if (prev)
			prev->next = node;
		else
			head = node;
		prev = node;
		i++;
	}
	return (head);
}

/* Check if a variable name is valid */
int	is_valid_var_name(const char *name)
{
	if (!name || !*name || ft_isdigit(*name))
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

static void	put_env_line(const char *k, const char *v)
{
	char	*line;
	char	*full;

	line = ft_strjoin(k, "=");
	if (!line)
		return ;
	full = ft_strjoin(line, v);
	if (!full)
		return ;
	write(1, full, ft_strlen(full));
	write(1, "\n", 1);
}

void	display_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			put_env_line(tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
