/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:07:41 by scambier          #+#    #+#             */
/*   Updated: 2023/11/22 15:39:42 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "get_next_line_bonus.h"

int	min_max(int a, int b, int f)
{
	if (f > 0)
		return ((a >= b) * a + (a < b) * b);
	else if (f < 0)
		return ((a <= b) * a + (a > b) * b);
	return (0);
}

void	ft_strnset(char *str, char c, int n)
{
	while (--n >= 0)
		str[n] = c;
}

int	ft_strlen(const char *str)
{
	int	k;

	k = 0;
	while (str[k])
		k++;
	return (k);
}

int	has_char(char *str, char c)
{
	int	k;

	k = -1;
	while (str[++k])
		if (str[k] == c)
			return (k);
	return (-1);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		target_len;
	int		s_len;
	char	*out;
	int		k;

	s_len = ft_strlen(s);
	target_len = min_max(min_max(len, s_len
				- min_max(start, s_len, -1), -1), 0, 1);
	out = malloc(sizeof(char) * (target_len + 1));
	if (!out)
		return (0);
	k = -1;
	while (++k < target_len)
		out[k] = s[start + k];
	out[target_len] = 0;
	return (out);
}
