/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-arib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:31:35 by yel-arib          #+#    #+#             */
/*   Updated: 2025/08/30 04:31:54 by yel-arib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	accumulate_with_overflow(const char *s, int *i, int neg, long long *acc)
{
	int	digit;

	*acc = 0;
	if (s[*i] < '0' || s[*i] > '9')
		return (0);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		digit = s[*i] - '0';
		if (!neg)
		{
			if (*acc > (LLONG_MAX - digit) / 10)
				return (0);
			*acc = *acc * 10 + digit;
		}
		else
		{
			if (*acc < (LLONG_MIN + digit) / 10)
				return (0);
			*acc = *acc * 10 - digit;
		}
		(*i)++;
	}
	return (1);
}

int	parse_ll_with_overflow(const char *s, long long *out)
{
	int	i;
	int	neg;

	i = 0;
	skip_spaces(s, &i);
	neg = parse_sign(s, &i);
	if (!accumulate_with_overflow(s, &i, neg, out))
		return (0);
	skip_spaces(s, &i);
	if (s[i])
		return (0);
	return (1);
}
