/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:19 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:52:20 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_external(t_cmd *cmd, t_env *env, char **envp)
{
	char	*path;
	int		error_code;
	int		err;

	error_code = validate_command_input(cmd);
	if (error_code != 0)
		return (error_code);
	path = find_path(cmd->argv[0], env);
	if (!path)
	{
		print_command_not_found(cmd->argv[0]);
		return (127);
	}
	error_code = check_path_permissions(path);
	if (error_code != 0)
		return (error_code);
	execve(path, cmd->argv, envp);
	{
		err = errno;
		perror("execve");
		if (err == ENOENT)
			return (127);
		else
			return (126);
	}
}
