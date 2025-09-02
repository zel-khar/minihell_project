/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: zakel-kh <zakel-kh@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/08/29 16:16:43 by zakel-kh          #+#    #+#             */
/*   Updated: 2025/08/29 16:16:43 by zakel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../inc/minishell.h"
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strlen(char const *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_itoa(int n);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
int		parse_ll_with_overflow(const char *s, long long *out);
int		accumulate_with_overflow(const char *s, int *i, int neg,
			long long *acc);
int		parse_sign(const char *s, int *i);
void	skip_spaces(const char *s, int *i);
int		ft_isdigit(int c);

#endif
