/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:22:12 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:22:14 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*read_heredoc_line(t_shell *shell)
{
	char	*line;
	int		saved_stderr;
	int		devnull;

	if (shell->interactive)
	{
		line = readline("> ");
	}
	else
	{
		saved_stderr = dup(STDERR_FILENO);
		devnull = open("/dev/null", O_WRONLY);
		if (devnull != -1)
		{
			dup2(devnull, STDERR_FILENO);
			close(devnull);
		}
		line = readline(NULL);
		if (saved_stderr != -1)
		{
			dup2(saved_stderr, STDERR_FILENO);
			close(saved_stderr);
		}
	}
	return (line);
}

void	handle_heredoc_eof(int wfd, const char *delim, t_shell *shell)
{
	char	*ln;

	ln = ft_itoa(shell->line_no);
	write(2, "minishell: warning: here-document at line ", 43);
	if (ln)
		write(2, ln, ft_strlen(ln));
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
	close(wfd);
	ft_exit(0);
}

int	process_heredoc_line(char **line, const char *delim, int quoted, int wfd)
{
	char	*exp;

	if (!quoted)
	{
		exp = expand_line(*line, store_shell(NULL));
		if (!exp)
		{
			close(wfd);
			ft_exit(1);
		}
		if (!ft_strcmp(exp, delim))
		{
			close(wfd);
			ft_exit(0);
		}
		*line = exp;
	}
	else if (!ft_strcmp(*line, delim))
	{
		close(wfd);
		ft_exit(0);
	}
	return (1);
}

void	heredoc_child_loop(int wfd, const char *delim, int quoted,
		t_shell *shell)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = read_heredoc_line(shell);
		if (!line)
			handle_heredoc_eof(wfd, delim, shell);
		if (!process_heredoc_line(&line, delim, quoted, wfd))
			continue ;
		write(wfd, line, ft_strlen(line));
		write(wfd, "\n", 1);
	}
}
