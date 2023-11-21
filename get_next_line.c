/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:40:22 by scambier          #+#    #+#             */
/*   Updated: 2023/11/21 15:49:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	k;

	k = 0;
	while (str[k])
		k++;
	return (k);
}

void	ft_strmcat(char **dst, char *src)
{
	char	*out;
	int		dst_len;
	int		src_len;
	int		k;

	dst_len = ft_strlen(*dst);
	src_len = ft_strlen(src);
	out = malloc((dst_len + src_len + 1) * sizeof(char));
	k = 0;
	while (k < (dst_len + src_len))
	{
		if (k < dst_len)
			out[k] = (*dst)[k];
		else
		{
			if (src[k - dst_len] == -1)
				break ;
			out[k] = src[k - dst_len];
		}
		k++;
	}
	out[k] = 0;
	free(*dst);
	*dst = out;
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

int	sep(char *A, char *B, char *src)
{
	int	flag;

	flag = 0;
	while (*src)
	{
		if (!flag)
			*A++ = *src;
		else
		{
			*B++ = *src;
			*src = 0;
		}
		if (*src == '\n' || *src == -1)
			flag = 1;
		src++;
	}
	return (flag);
}

void	ft_strncpy(char *dst, char *src, int n)
{
	dst[n] = 0;
	while (--n >= 0)
		dst[n] = src[n];
}

void	ft_strnset(char *dst, char c, int n)
{
	while (n >= 0)
		dst[n--] = c;
}

char	*ft_stralloc(int len, char c)
{
	char	*out;

	out = malloc(len);
	if (!out)
		return (0);
	while (--len >= 0)
		out[len] = c;
	return (out);
}
static size_t	min(size_t a, size_t b)
{
	return ((a <= b) * a + (a > b) * b);
}

static size_t	max(size_t a, size_t b)
{
	return ((a >= b) * a + (a < b) * b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	target_len;
	size_t	s_len;
	char	*out;
	size_t	k;

	s_len = ft_strlen(s);
	target_len = max(min(len, s_len - min(start, s_len)), 0);
	out = malloc(sizeof(char) * (target_len + 1));
	if (!out)
		return (0);
	k = -1;
	while (++k < target_len)
		out[k] = s[start + k];
	out[target_len] = 0;
	return (out);
}
void	ft_moise(char **out, char **in)
{
	char	*new_in;
	int		in_len;
	int		bn_index;

	if (!*in)
		return ;
	in_len = ft_strlen(*in);
	bn_index = has_char(*in, 10);
	if (bn_index == -1)
		bn_index = in_len;
	*out = ft_substr(*in, 0, bn_index + 1);
	if (bn_index == in_len)
		new_in = 0;
	else
		new_in = ft_substr(*in, bn_index + 1,  in_len - bn_index + 1);
	free(*in);
	*in = new_in;
}

void	ft_read(int fd, char **out)
{
	char	*buffer;
	int		read_len;

	if (!*out)
		*out = ft_stralloc(1, 0);
	buffer = ft_stralloc(BUFFER_SIZE + 1, 0);
	while (1)
	{
		if (has_char(*out, 10) != -1)
			break ;
		ft_strnset(buffer, 0, BUFFER_SIZE);
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == 0) 
		{
			if (ft_strlen(*out) > 0)
				break;
			free(*out);
			*out = 0;
			break ;
		}
		ft_strmcat(out, buffer);
		if (read_len < BUFFER_SIZE)
			break;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*out;

	out = 0;
	if (read(fd, 0, 0) < 0)
		return (0);
	ft_read(fd, &buffer);
	if (buffer)
		ft_moise(&out, &buffer);
	return (out);
}

// char	*get_next_line(int fd)
// {
// 	char 		buffer[BUFFER_SIZE + 1];
// 	char		*out;
// 	int			read_size;
// 	static char	prev[BUFFER_SIZE + 1];

// 	out = malloc(1);
// 	*out = 0;
// 	ft_strcpy(buffer, prev);
// 	ft_strnset(prev, 0, BUFFER_SIZE);
// 	while (1)
// 	{
// 		int a = sep(buffer, prev, buffer);
// 		ft_strmcat(&out, buffer);
// 		if (a)
// 			break;
// 		ft_strnset(buffer, 0, BUFFER_SIZE);
// 		read_size = read(fd, buffer, BUFFER_SIZE);
// 		buffer[read_size] = ((read_size < BUFFER_SIZE) * -1);
// 		if (!has_char(buffer, '\n') && read_size <= 0)
// 		{
// 			free(out);
// 			return (0);
// 		}
// 	}
// 	return (out);
// }