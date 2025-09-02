/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:12 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:58:46 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_token_output(char *value, t_tokbuild *tb, int quoted)
{
	t_token	*new;

	if (!quoted && !*(tb->heredoc_delim))
	{
		if (!add_splitted_tokens(value, tb->head))
			return (0);
	}
	else
	{
		restore_ws(value);
		new = tok_token_new(value, TOKEN_WORD, quoted);
		if (!new)
			return (*(tb->head) = NULL, 0);
		tok_token_add_back(tb->head, new);
	}
	return (1);
}

static int	handle_word_token(const char *str, int *i, t_tokbuild *tb)
{
	int			quoted;
	char		*value;
	t_tokctx	ctx;

	if (*(tb->heredoc_delim))
		quoted = 0;
	else
		quoted = 1;
	setup_token_context(&ctx, tb, &quoted);
	value = tok_expand_word(str, i, &ctx);
	if (*(tb->err) || !value)
		return (*(tb->head) = NULL, 0);
	if (!process_heredoc_expansion(&value, tb, quoted))
		return (*(tb->head) = NULL, 0);
	if (!handle_token_output(value, tb, quoted))
	{
		return (0);
	}
	*(tb->heredoc_delim) = 0;
	return (1);
}

static void	init_tokenize_vars(t_token **head, int *heredoc_delim,
		t_tokbuild *tb, t_shell *shell)
{
	*head = NULL;
	*heredoc_delim = 0;
	tb->head = head;
	tb->heredoc_delim = heredoc_delim;
	tb->shell = shell;
}

static int	process_token(const char *str, int *i, t_tokbuild *tb)
{
	*i = tok_skip_spaces(str, *i);
	if (!str[*i])
		return (1);
	if (tok_is_operator(str[*i]))
	{
		if (!handle_operator_token(str, i, tb->head, tb->heredoc_delim))
			return (0);
	}
	else if (!handle_word_token(str, i, tb))
		return (0);
	return (1);
}

t_token	*tokenize(const char *str, t_shell *shell, int *err)
{
	t_token		*head;
	int			i;
	int			heredoc_delim;
	t_tokbuild	tb;

	*err = 0;
	tb.err = err;
	i = 0;
	init_tokenize_vars(&head, &heredoc_delim, &tb, shell);
	while (str[i])
	{
		if (!process_token(str, &i, &tb))
			return (NULL);
		if (!str[i])
			break ;
	}
	return (head);
}
