/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:14 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:49:36 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_command_not_found(const char *cmd_name)
{
	const char	*suffix;
	size_t		len;
	char		*buf;

	suffix = ": command not found\n";
	len = 11 + ft_strlen(cmd_name) + ft_strlen(suffix);
	buf = (char *)ft_malloc(len + 1);
	if (!buf)
		return ;
	ft_memcpy(buf, "minishell: ", 11);
	ft_memcpy(buf + 11, cmd_name, ft_strlen(cmd_name));
	ft_memcpy(buf + 11 + ft_strlen(cmd_name), suffix, ft_strlen(suffix));
	buf[len] = '\0';
	write(2, buf, len);
}

int	validate_command_input(t_cmd *cmd)
{
	char	*name;

	if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		if (cmd && cmd->argv && cmd->argv[0])
			name = cmd->argv[0];
		else
			name = "";
		print_command_not_found(name);
		return (127);
	}
	return (0);
}

static void	print_error(const char *path, const char *msg)
{
	size_t	len_path;
	size_t	len_msg;
	size_t	total_len;
	char	*buf;

	len_path = ft_strlen(path);
	len_msg = ft_strlen(msg);
	total_len = 11 + len_path + len_msg;
	buf = (char *)ft_malloc(total_len + 1);
	if (buf)
	{
		ft_memcpy(buf, "minishell: ", 11);
		ft_memcpy(buf + 11, path, len_path);
		ft_memcpy(buf + 11 + len_path, msg, len_msg);
		buf[total_len] = '\0';
		write(2, buf, total_len);
	}
}

int	check_path_permissions(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (print_error(path, ": Is a directory\n"), 126);
		if (access(path, X_OK) != 0)
			return (print_error(path, ": Permission denied\n"), 126);
	}
	return (0);
}
