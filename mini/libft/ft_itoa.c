/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:15:33 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 17:03:29 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digits_len(long v)
{
	size_t	l;

	l = 1;
	if (v < 0)
		v = -v;
	while (v >= 10)
	{
		l++;
		v /= 10;
	}
	return (l);
}

static void	write_digits(char *s, long v, size_t nd, size_t total)
{
	while (nd-- > 0)
	{
		s[total - 1] = (char)('0' + (v % 10));
		v /= 10;
		total--;
	}
}

char	*ft_itoa(int n)
{
	long	v;
	size_t	nd;
	size_t	total;
	int		neg;
	char	*s;

	v = n;
	neg = (v < 0);
	nd = digits_len(v);
	if (neg)
		total = nd + 1;
	else
		total = nd;
	s = ft_malloc(total + 1);
	if (!s)
		return (NULL);
	s[total] = '\0';
	if (neg)
	{
		v = -v;
		s[0] = '-';
	}
	write_digits(s, v, nd, total);
	return (s);
}

void	skip_spaces(const char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

int	parse_sign(const char *s, int *i)
{
	int	neg;

	neg = 0;
	if (s[*i] == '+' || s[*i] == '-')
		neg = (s[(*i)++] == '-');
	return (neg);
}
