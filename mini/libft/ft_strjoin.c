/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/08/29 16:16:27 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:16:27 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_str(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *a, char const *b)
{
	size_t	la;
	size_t	lb;
	char	*res;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	res = ft_malloc(la + lb + 1);
	if (!res)
		return (NULL);
	copy_str(res, a, la);
	copy_str(res + la, b, lb);
	res[la + lb] = '\0';
	return (res);
}
