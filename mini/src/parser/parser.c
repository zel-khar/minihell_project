/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:03 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:19:04 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Count argv entries for a single command segment (until a pipe or end),
 * ignoring redirection targets. This allows arguments to appear before or
 * after redirections, like in: echo a > out b
 */

static int	set_redir(t_cmd *cmd, t_token *tok)
{
	if (tok->type == 2)
	{
		cmd->infile = ft_strdup(tok->next->value);
		add_redir(cmd, tok->type, tok->next->value);
	}
	if (tok->type == 3)
	{
		cmd->outfile = ft_strdup(tok->next->value);
		cmd->append = 0;
		add_redir(cmd, tok->type, tok->next->value);
	}
	if (tok->type == 4)
	{
		cmd->heredoc_delimiter = ft_strdup(tok->next->value);
		cmd->heredoc_quoted = tok->next->quoted;
		add_heredoc_redir(cmd, tok->next->value, tok->next->quoted);
	}
	if (tok->type == 5)
	{
		cmd->outfile = ft_strdup(tok->next->value);
		cmd->append = 1;
		add_redir(cmd, tok->type, tok->next->value);
	}
	return (0);
}

/*
 * Fill argv for one command by scanning tokens until a pipe or end.
 * Redirections are applied to the command, and their targets are not
 * added to argv. Arguments can appear anywhere relative to redirections.
 */
static int	allocate_argv_array(t_cmd *cur, int argc)
{
	if (argc > 0)
	{
		cur->argv = (char **)ft_malloc(sizeof(char *) * (argc + 1));
		if (!cur->argv)
			return (-1);
	}
	return (0);
}

static void	process_token_scan(t_cmd *cur, t_token **scan, int *i, int argc)
{
	if ((*scan) && (*scan)->next && (*scan)->next->value
		&& is_redir((*scan)->type))
	{
		set_redir(cur, *scan);
		*scan = (*scan)->next;
		if (*scan)
			*scan = (*scan)->next;
	}
	else if ((*scan)->type == TOKEN_WORD)
	{
		if (argc > 0)
			cur->argv[(*i)++] = ft_strdup((*scan)->value);
		*scan = (*scan)->next;
	}
	else
		*scan = (*scan)->next;
}

static int	fill_argv_from_tokens(t_cmd *cur, t_token **tok)
{
	int		argc;
	int		i;
	t_token	*scan;

	argc = count_cmd_args(*tok);
	if (argc < 0)
		return (-1);
	if (allocate_argv_array(cur, argc) == -1)
		return (-1);
	i = 0;
	scan = *tok;
	while (scan && scan->type != TOKEN_PIPE)
		process_token_scan(cur, &scan, &i, argc);
	if (argc > 0)
		cur->argv[i] = NULL;
	*tok = scan;
	return (0);
}

t_cmd	*parse_commands(t_token *tok, int *err)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	while (tok)
	{
		cur = append_new_cmd(&head, cur);
		if (!cur)
			return (NULL);
		if (fill_argv_from_tokens(cur, &tok) == -1)
			return (*err = 1, NULL);
		if (tok && tok->type == TOKEN_PIPE)
		{
			cur->next = NULL;
			cur = NULL;
			tok = tok->next;
		}
		else
			break ;
	}
	return (head);
}
