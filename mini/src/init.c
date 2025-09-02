/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:28 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:19:29 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_shell	*store_shell(t_shell *shell)
{
	static t_shell	*save;

	if (shell)
		save = shell;
	return (save);
}

void	init_shell(t_shell *shell, char **envp)
{
	store_shell(shell);
	shell->envp = envp;
	shell->exit_status = 0;
	shell->env_list = copy_env(envp);
	rl_outstream = stderr;
	shell->interactive = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
	if (!shell->interactive)
	{
		rl_inhibit_completion = 1;
	}
	shell->line_no = 1;
	shell->saved_stdin_fd = -1;
	shell->is_subshell = 0;
	setup_signals();
}
