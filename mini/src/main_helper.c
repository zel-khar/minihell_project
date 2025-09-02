/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:31:05 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:31:14 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_input(t_shell *shell, char *prompt)
// {
	// (void) prompt;
	// char	*input;
	// int		sstderr;
	// int		devnull;

	// if (shell->interactive)
	// return (readline(prompt));
	// sstderr = dup(STDERR_FILENO);
	// devnull = open("/dev/null", O_WRONLY);
	// dup2(devnull, STDERR_FILENO);
	// close(devnull);
	// input = readline(NULL);
	// dup2(sstderr, STDERR_FILENO);
	// close(sstderr);
	// return (input);
// }

int	process_line(t_shell *shell, char *line)
{
	int	err;

	err = 0;
	shell->tokens = tokenize(line, shell, &err);
	if (!err && !validate_syntax(shell->tokens))
	{
		err = 1;
	}
	if (!err)
	{
		shell->cmds = parse_commands(shell->tokens, &err);
		if (!err)
			shell->exit_status = execute_pipeline(shell->cmds, &shell->env_list,
					shell->envp, shell);
		if (shell->exit_status == 131)
			write(2, "Quit\n", 5);
		else if (shell->exit_status == 130)
			write(2, "\n", 1);
	}
	if (err)
		shell->exit_status = 2;
	return (err);
}

void	cleanup_after_command(t_shell *shell)
{
	shell->tokens = NULL;
	shell->cmds = NULL;
	if (shell->saved_stdin_fd != -1)
	{
		dup2(shell->saved_stdin_fd, STDIN_FILENO);
		close(shell->saved_stdin_fd);
		shell->saved_stdin_fd = -1;
	}
}
