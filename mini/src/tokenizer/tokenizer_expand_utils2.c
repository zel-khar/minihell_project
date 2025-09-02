/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_expand_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:23:50 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:23:52 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tok_handle_env(const char *str, int *i, t_env *env, t_shell *shell)
{
	int		start;
	char	*key;
	char	*val;

	start = *i;
	(*i)++;
	if (str[*i] == '?')
		return ((*i)++, ft_itoa(shell->exit_status));
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		(*i)++;
	key = ft_strndup(str + start + 1, *i - start - 1);
	if (!key)
		return (NULL);
	{
		val = tok_env_value_for_key(env, key);
		return (val);
	}
}

int	find_closing_quote(const char *str, int start, char quote)
{
	int	j;

	j = start + 1;
	while (str[j] && str[j] != quote)
		j++;
	return (j);
}

char	*handle_quote_expansion(char *content, char quote, t_tokctx *ctx)
{
	char	*expanded;

	if (quote == '"' && !ctx->heredoc)
	{
		expanded = tok_expand_inner(content, ctx->env, ctx->shell);
		content = expanded;
		if (!content)
			return (NULL);
	}
	return (content);
}

void	protect_whitespace(char *content)
{
	int	k;

	k = 0;
	while (content && content[k])
	{
		if (content[k] == ' ' || content[k] == '\t')
			content[k] = (char)TOK_WS_SENTINEL;
		k++;
	}
}

char	*tok_handle_quotes(const char *str, int *i, t_tokctx *ctx)
{
	char	quote;
	int		j;
	char	*content;

	quote = str[*i];
	j = find_closing_quote(str, *i, quote);
	if (!str[j])
		return (*(ctx->err) = 1, NULL);
	content = ft_strndup(str + *i + 1, j - *i - 1);
	if (!content)
		return (NULL);
	content = handle_quote_expansion(content, quote, ctx);
	if (!content)
		return (NULL);
	*i = j + 1;
	protect_whitespace(content);
	return (content);
}
