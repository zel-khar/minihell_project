/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:04 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:18:05 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_path_entries(const char *path)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	if (!path)
		return (1);
	while (path[i])
		if (path[i++] == ':')
			count++;
	return (count);
}

static void	fill_path_array(char **arr, const char *path)
{
	int	idx;
	int	start;
	int	i;

	idx = 0;
	start = 0;
	i = 0;
	while (1)
	{
		if (path[i] == ':' || path[i] == '\0')
		{
			if (i - start > 0)
				arr[idx++] = ft_strndup(path + start, i - start);
			else
				arr[idx++] = ft_strdup("");
			if (path[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	arr[idx] = NULL;
}

char	**split_path_preserve_empty(const char *path)
{
	int		count;
	char	**arr;

	if (!path)
		path = ".";
	count = count_path_entries(path);
	arr = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	fill_path_array(arr, path);
	return (arr);
}
