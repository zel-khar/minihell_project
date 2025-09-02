/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_external.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:00 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/30 00:50:56 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_child_process(t_cmd *cmd, t_env **env, char **envp)
{
	setup_signals();
	if (apply_all_redirs(cmd) == -1)
		ft_exit(1);
	ft_exit(exec_external(cmd, *env, envp));
	return (0);
}

static int	handle_parent_process(pid_t pid, int saved_stdin)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		if (saved_stdin != -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		setup_signals();
		return (1);
	}
	setup_signals();
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	run_external_single(t_cmd *cmd, t_env **env, char **envp, int saved_stdin)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		return (handle_child_process(cmd, env, envp));
	if (pid > 0)
		return (handle_parent_process(pid, saved_stdin));
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	perror("fork");
	return (1);
}
