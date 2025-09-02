/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:24 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:17:25 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unset_one(const char *name, t_env **env)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, name))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
		unset_one(argv[i++], env);
	return (0);
}
