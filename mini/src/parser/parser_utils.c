/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:54 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:18:55 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->heredoc_quoted = 0;
	cmd->append = 0;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(int type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

void	add_redir(t_cmd *cmd, int type, const char *file)
{
	t_redir	*node;
	t_redir	*it;

	if (!cmd || !file)
		return ;
	node = (t_redir *)ft_malloc(sizeof(t_redir));
	node->type = type;
	node->file = ft_strdup(file);
	node->append = (type == TOKEN_APPEND);
	node->quoted = 0;
	node->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = node;
	else
	{
		it = cmd->redirs;
		while (it->next)
			it = it->next;
		it->next = node;
	}
}

void	add_heredoc_redir(t_cmd *cmd, const char *delim, int quoted)
{
	t_redir	*node;
	t_redir	*it;

	if (!cmd || !delim)
		return ;
	node = (t_redir *)ft_malloc(sizeof(t_redir));
	node->type = TOKEN_HEREDOC;
	node->file = ft_strdup(delim);
	node->append = 0;
	node->quoted = quoted;
	node->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = node;
	else
	{
		it = cmd->redirs;
		while (it->next)
			it = it->next;
		it->next = node;
	}
}
