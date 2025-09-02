/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:31 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:18:32 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	setup_pipe_and_fork(t_cmd *cur, int *prev_fd, int *pipe_fd,
		int saved_stdin)
{
	pid_t	pid;

	if (cur->next && pipe(pipe_fd) == -1)
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		if (saved_stdin != -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		return (perror("pipe"), -1);
	}
	pid = fork();
	if (pid == 0)
	{
		store_shell(NULL)->is_subshell = 1;
		spawn_child(*prev_fd, pipe_fd, cur, store_shell(NULL));
	}
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	return (pid);
}

static void	cleanup_pipe_fds(int *prev_fd, int *pipe_fd, t_cmd *cur)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cur->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

static int	process_pipeline_cmd(t_cmd *cur, int *prev_fd, int *pipe_fd,
		pid_t *last_cmd)
{
	int	saved_stdin;

	saved_stdin = -1;
	if (prep_heredoc(cur, store_shell(NULL), &saved_stdin))
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		return (1);
	}
	*last_cmd = setup_pipe_and_fork(cur, prev_fd, pipe_fd, saved_stdin);
	store_shell(NULL)->saved_stdin_fd = -1;
	if (*last_cmd == -1)
		return (1);
	cleanup_pipe_fds(prev_fd, pipe_fd, cur);
	return (0);
}

static int	wait_for_last_cmd(pid_t last_cmd)
{
	int	status;

	while (waitpid(last_cmd, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

int	pipeline_loop(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cur;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	last_cmd;

	prev_fd = -1;
	cur = cmds;
	while (cur)
	{
		if (process_pipeline_cmd(cur, &prev_fd, pipe_fd, &last_cmd))
			return (shell->exit_status);
		cur = cur->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (wait_for_last_cmd(last_cmd));
}
