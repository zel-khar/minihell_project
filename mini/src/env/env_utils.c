/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:18:33 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:18:35 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_equals_in_entry(const char *entry)
{
	int		k;
	char	*eq;

	k = 0;
	eq = NULL;
	while (entry[k])
	{
		if (entry[k] == '=')
		{
			eq = (char *)(entry + k);
			break ;
		}
		k++;
	}
	return (eq);
}

void	set_env_key_value(t_env *new, const char *entry, char *eq)
{
	if (eq)
	{
		new->key = ft_strdup(entry);
		*(new->key + (eq - entry)) = '\0';
		new->value = ft_strdup(eq + 1);
	}
	else
	{
		new->key = ft_strdup(entry);
		new->value = NULL;
	}
}
