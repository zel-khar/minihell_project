/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:46 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/30 00:43:15 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(int status)
{
	ft_cleanup(NULL);
	exit(status);
}

static void	setup_output_redir(t_cmd *cmd)
{
	int	flags;
	int	fd;

	if (!cmd->outfile)
		return ;
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd == -1)
	{
		perror("open");
		ft_exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

int	child_process(t_cmd *cmd, t_env *env, char **envp, int in_fd)
{
	if (cmd->infile)
		in_fd = open(cmd->infile, O_RDONLY);
	setup_output_redir(cmd);
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (cmd->pipe_fd[1] != -1)
	{
		dup2(cmd->pipe_fd[1], 1);
		close(cmd->pipe_fd[1]);
	}
	return (exec_external(cmd, env, envp));
}

int	wait_for_children(int n, int *status)
{
	int	ret;
	int	i;

	i = 0;
	while (i++ < n)
		ret = wait(status);
	return (ret);
}
