/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:12:46 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:12:51 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_cmd_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != TOKEN_PIPE)
	{
		if (is_redir(tok->type))
		{
			tok = tok->next;
			if (tok)
				tok = tok->next;
			continue ;
		}
		if (tok->type == TOKEN_WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}

t_cmd	*append_new_cmd(t_cmd **head, t_cmd *cur)
{
	t_cmd	*tmp;

	if (cur)
		return (cur);
	cur = cmd_new();
	if (!*head)
		*head = cur;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cur;
	}
	return (cur);
}
