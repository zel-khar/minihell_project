/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:46 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:17:47 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	restore_std_streams(int saved_out, int saved_in)
{
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
}

void	close_saved_streams(int saved_out, int saved_in)
{
	if (saved_out != -1)
		close(saved_out);
	if (saved_in != -1)
		close(saved_in);
}

int	is_exit_cmd(t_cmd *cmd)
{
	if (cmd->argv && cmd->argv[0] && !ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

int	return_with_reset(int ret, t_shell *shell)
{
	shell->saved_stdin_fd = -1;
	return (ret);
}
