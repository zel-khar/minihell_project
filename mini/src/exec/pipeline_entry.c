/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:23 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/30 02:00:36 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_cmd *cmds, t_env **env, char **envp, t_shell *shell)
{
	t_cmd	*cur;
	int		count;

	if (!cmds)
		return (0);
	cur = cmds;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	if (count == 1)
		return (execute_single_cmd(cmds, env, envp, shell));
	return (pipeline_loop(cmds, shell));
}
