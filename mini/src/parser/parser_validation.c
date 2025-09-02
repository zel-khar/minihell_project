/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:18:58 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:56:51 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	put_str(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

static void	syntax_err_msg(int type)
{
	const char	*tok;

	if (type == TOKEN_REDIR_IN)
		tok = "<";
	else if (type == TOKEN_REDIR_OUT)
		tok = ">";
	else if (type == TOKEN_HEREDOC)
		tok = "<<";
	else if (type == TOKEN_APPEND)
		tok = ">>";
	else
		tok = "newline";
	put_str(2, "minishell: syntax error near unexpected token `");
	put_str(2, tok);
	put_str(2, "'\n");
}

int	validate_syntax(t_token *tok)
{
	if (!tok)
		return (1);
	if (tok->type == TOKEN_PIPE)
		return (put_str(2,
				"minishell: syntax error near unexpected token `|'\n"), 0);
	while (tok)
	{
		if (tok->type == TOKEN_PIPE && (!tok->next
				|| tok->next->type == TOKEN_PIPE))
			return (put_str(2,
					"minishell: syntax error near unexpected token `|'\n"), 0);
		if (tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_APPEND)
		{
			if (!tok->next || tok->next->type != TOKEN_WORD)
			{
				if (tok->next)
					syntax_err_msg(tok->next->type);
				else
					syntax_err_msg(-1);
				return (0);
			}
		}
		tok = tok->next;
	}
	return (1);
}
