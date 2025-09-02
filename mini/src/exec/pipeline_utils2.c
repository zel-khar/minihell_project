/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:21:18 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:21:19 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	prep_heredoc(t_cmd *cmd, t_shell *shell, int *saved_stdin)
{
	t_redir	*it;
	int		found;

	if (!cmd)
		return (0);
	found = 0;
	it = cmd->redirs;
	while (it)
	{
		if (it->type == TOKEN_HEREDOC)
		{
			found = 1;
			break ;
		}
		it = it->next;
	}
	if (!found && !cmd->heredoc_delimiter)
		return (0);
	*saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdin_fd = *saved_stdin;
	if (process_heredoc_redirs(cmd->redirs, *saved_stdin, shell))
		return (1);
	if (!found && process_cmd_heredoc(cmd, *saved_stdin, shell))
		return (1);
	return (0);
}
