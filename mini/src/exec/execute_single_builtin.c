/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:50 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:17:51 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_single_builtin(t_cmd *cmd, t_env **env, t_shell *shell, int saved_stdin)
{
	int	saved_out;
	int	ret;
	int	loc_saved_stdin;

	saved_out = dup(STDOUT_FILENO);
	loc_saved_stdin = saved_stdin;
	if (loc_saved_stdin == -1)
		loc_saved_stdin = dup(STDIN_FILENO);
	if (apply_all_redirs(cmd) == -1)
	{
		restore_std_streams(saved_out, loc_saved_stdin);
		return (1);
	}
	if (is_exit_cmd(cmd))
	{
		close_saved_streams(saved_out, loc_saved_stdin);
		return (execute_builtin(cmd, env, shell));
	}
	ret = execute_builtin(cmd, env, shell);
	restore_std_streams(saved_out, loc_saved_stdin);
	return (ret);
}

int	handle_empty_command(t_cmd *cmd, int saved_stdin)
{
	int	saved_stdout;
	int	ret;
	int	loc_saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	loc_saved_stdin = saved_stdin;
	if (loc_saved_stdin == -1)
		loc_saved_stdin = dup(STDIN_FILENO);
	ret = 0;
	if (apply_all_redirs(cmd) == -1)
		ret = 1;
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (loc_saved_stdin != -1)
	{
		dup2(loc_saved_stdin, STDIN_FILENO);
		close(loc_saved_stdin);
	}
	return (ret);
}
