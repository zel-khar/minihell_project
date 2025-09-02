/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:23:09 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:23:12 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_operator_token(const char *str, int *i, t_token **head,
		int *heredoc_delim)
{
	int		type;
	char	*value;
	t_token	*new;

	type = tok_get_token_type(str, *i);
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
	{
		value = ft_strndup(str + (*i), 2);
		*i += 2;
	}
	else
		value = ft_strndup(str + (*i)++, 1);
	new = tok_token_new(value, type, 0);
	if (!new)
	{
		return (*head = NULL, 0);
	}
	tok_token_add_back(head, new);
	if (type == TOKEN_HEREDOC)
		*heredoc_delim = 1;
	return (1);
}

void	restore_ws(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)TOK_WS_SENTINEL)
			s[i] = ' ';
		i++;
	}
}

int	add_splitted_tokens(char *value, t_token **head)
{
	int		i;
	int		start;
	t_token	*new;
	char	*part;

	i = 0;
	while (value[i])
	{
		while (value[i] && (value[i] == ' ' || value[i] == '\t'))
			i++;
		if (!value[i])
			break ;
		start = i;
		while (value[i] && value[i] != ' ' && value[i] != '\t')
			i++;
		part = ft_strndup(value + start, i - start);
		if (!part)
			return (*head = NULL, 0);
		restore_ws(part);
		new = tok_token_new(part, TOKEN_WORD, 0);
		if (!new)
			return (*head = NULL, 0);
		tok_token_add_back(head, new);
	}
	return (1);
}

void	setup_token_context(t_tokctx *ctx, t_tokbuild *tb, int *quoted)
{
	ctx->env = tb->shell->env_list;
	ctx->shell = tb->shell;
	ctx->heredoc = *(tb->heredoc_delim);
	ctx->err = tb->err;
	ctx->res = NULL;
	ctx->quoted = quoted;
}

int	process_heredoc_expansion(char **value, t_tokbuild *tb, int quoted)
{
	char	*expanded;

	if (*(tb->heredoc_delim) && !quoted)
	{
		expanded = expand_line(*value, tb->shell);
		if (!expanded)
			return (0);
		*value = expanded;
	}
	return (1);
}
