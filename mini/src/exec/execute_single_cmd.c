/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:56 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:17:57 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_single_cmd(t_cmd *cmd, t_env **env, char **envp, t_shell *shell)
{
	int	saved_stdin;
	int	ret;

	if (!cmd)
		return (0);
	saved_stdin = -1;
	if (prep_heredoc(cmd, shell, &saved_stdin))
		return (return_with_reset(shell->exit_status, shell));
	if (!cmd->argv || !cmd->argv[0])
	{
		ret = handle_empty_command(cmd, saved_stdin);
		return (return_with_reset(ret, shell));
	}
	if (is_builtin(cmd->argv[0]))
	{
		ret = run_single_builtin(cmd, env, shell, saved_stdin);
		return (return_with_reset(ret, shell));
	}
	ret = run_external_single(cmd, env, envp, saved_stdin);
	return (return_with_reset(ret, shell));
}
