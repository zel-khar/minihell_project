/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:19:19 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:19:20 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_quoted_segment(const char *s, int *i, t_tokctx *ctx,
		char **res)
{
	char	*part;

	if (ctx->heredoc && ctx->quoted)
		*(ctx->quoted) = 1;
	part = tok_handle_quotes(s, i, ctx);
	if (!part)
		return (-1);
	return (join_part(res, part));
}

static int	handle_env_expansion(const char *s, int *i, t_tokctx *ctx,
		char **res)
{
	char	*part;

	part = tok_handle_env(s, i, ctx->env, ctx->shell);
	if (!part)
		return (-1);
	if (ctx->quoted)
		*(ctx->quoted) = 0;
	return (join_part(res, part));
}

static int	handle_literal_char(const char *s, int *i, t_tokctx *ctx,
		char **res)
{
	*res = tok_str_append_char(*res, s[*i]);
	(*i)++;
	if (!ctx->heredoc && ctx->quoted)
		*(ctx->quoted) = 0;
	if (*res)
		return (0);
	else
		return (-1);
}

static int	process_word_step(const char *s, int *i, t_tokctx *ctx, char **res)
{
	if (s[*i] == '\'' || s[*i] == '"')
		return (handle_quoted_segment(s, i, ctx, res));
	if (s[*i] == '$' && !ctx->heredoc)
		return (handle_env_expansion(s, i, ctx, res));
	return (handle_literal_char(s, i, ctx, res));
}

char	*tok_expand_word(const char *str, int *i, t_tokctx *ctx)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[*i] && !(str[*i] == ' ' || str[*i] == '\t' || str[*i] == '|'
			|| str[*i] == '<' || str[*i] == '>'))
	{
		if (process_word_step(str, i, ctx, &res) == -1)
			return (NULL);
	}
	return (res);
}
