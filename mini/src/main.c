/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:32 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/30 01:14:17 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_quote_syntax(const char *line)
{
	int		i;
	char	quote;
	int		flage;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			flage = 1;
			i++;
			while (line[i] && flage)
			{
				if (line[i] == quote)
					flage = 0;
				i++;
			}
			if (flage)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

static void	handle_input_signals(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
}

static int	handle_unclosed_quotes(t_shell *shell, char *line)
{
	if (check_quote_syntax(line))
	{
		shell->exit_status = 2;
		write(2, "minishell: unclosed quotes '\"'\n", 32);
		return (1);
	}
	return (0);
}

static void	run_loop(t_shell *shell)
{
	char	*line;
	char	*to_free;
	int		err;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		to_free = readline("minishell$ ");
		handle_input_signals(shell);
		if (!to_free)
		{
			cleanup_after_command(shell);
			break ;
		}
		line = ft_strdup(to_free);
		free(to_free);
		if (*line && shell->interactive)
			add_history(line);
		if (handle_unclosed_quotes(shell, line))
			continue ;
		err = process_line(shell, line);
		cleanup_after_command(shell);
		if (err && !shell->interactive)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	run_loop(&shell);
	rl_clear_history();
	ft_cleanup(NULL);
	return (shell.exit_status);
}
