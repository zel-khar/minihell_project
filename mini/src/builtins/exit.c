/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:17:12 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:17:13 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cleanup_and_exit(t_shell *shell, int status)
{
	shell->tokens = NULL;
	shell->cmds = NULL;
	ft_cleanup(NULL);
	exit(status);
}

static int	handle_no_args(t_shell *shell)
{
	if (shell->interactive && !shell->is_subshell)
		ft_putendl_fd("exit", 2);
	cleanup_and_exit(shell, shell->exit_status);
	return (0);
}

static int	handle_invalid_numeric(char **argv, t_shell *shell)
{
	if (shell->interactive && !shell->is_subshell)
		ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	cleanup_and_exit(shell, 2);
	return (0);
}

static int	handle_too_many_args(t_shell *shell)
{
	if (shell->interactive && !shell->is_subshell)
		ft_putendl_fd("exit", 2);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (1);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	long long	llval;
	int			status;

	if (!argv[1])
		return (handle_no_args(shell));
	if (!parse_ll_with_overflow(argv[1], &llval))
		return (handle_invalid_numeric(argv, shell));
	if (argv[2])
		return (handle_too_many_args(shell));
	if (shell->interactive && !shell->is_subshell)
		ft_putendl_fd("exit", 2);
	status = (int)((unsigned char)llval);
	cleanup_and_exit(shell, status);
	return (0);
}
