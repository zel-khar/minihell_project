/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:35 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/30 02:02:48 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_stdin(int saved_stdin, t_shell *shell)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	shell->saved_stdin_fd = -1;
	return (1);
}

int	process_heredoc_redirs(t_redir *it, int saved_stdin, t_shell *shell)
{
	while (it)
	{
		if (it->type == TOKEN_HEREDOC)
		{
			if (saved_stdin != -1)
				dup2(saved_stdin, STDIN_FILENO);
			if (handle_heredoc_execution(it->file, it->quoted, shell) == -1)
			{
				shell->exit_status = 130;
				return (restore_stdin(saved_stdin, shell));
			}
		}
		it = it->next;
	}
	return (0);
}

int	process_cmd_heredoc(t_cmd *cmd, int saved_stdin, t_shell *shell)
{
	if (cmd->heredoc_delimiter)
	{
		if (saved_stdin != -1)
			dup2(saved_stdin, STDIN_FILENO);
		if (handle_heredoc_execution(cmd->heredoc_delimiter,
				cmd->heredoc_quoted, shell) == -1)
		{
			shell->exit_status = 130;
			return (restore_stdin(saved_stdin, shell));
		}
	}
	return (0);
}

static int	execute_child_command(t_cmd *cur, t_shell *shell)
{
	if (!cur->argv || !cur->argv[0])
		return (0);
	else if (is_builtin(cur->argv[0]))
		return (execute_builtin(cur, &shell->env_list, shell));
	else
		return (exec_external(cur, shell->env_list, shell->envp));
}

int	spawn_child(int prev_fd, int *pipe_fd, t_cmd *cur, t_shell *shell)
{
	int	code;

	if (prev_fd != -1)
	{
		if (cur->heredoc_delimiter)
			close(prev_fd);
		else
		{
			dup2(prev_fd, 0);
			close(prev_fd);
		}
	}
	if (cur->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
	if (apply_all_redirs(cur) == -1)
		ft_exit(1);
	code = execute_child_command(cur, shell);
	shell->cmds = NULL;
	shell->tokens = NULL;
	ft_exit(code);
	return (0);
}
