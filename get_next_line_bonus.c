/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:40:22 by scambier          #+#    #+#             */
/*   Updated: 2024/01/23 17:03:04 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "get_next_line_bonus.h"

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
		new_in = ft_substr(*in, bn_index + 1, in_len - bn_index + 1);
	free(*in);
	*in = new_in;
}

void	ft_read(int fd, char **out)
{
	char	*buffer;
	int		read_len;

	if (!*out)
		*out = ft_stralloc(1, 0);
	if (has_char(*out, 10) != -1)
		return ;
	buffer = ft_stralloc(BUFFER_SIZE + 1, 0);
	while (1)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		buffer[read_len] = 0;
		if (read_len <= 0)
		{
			if (ft_strlen(*out) > 0)
				break ;
			free(*out);
			*out = 0;
			break ;
		}
		ft_strmcat(out, buffer);
		if (read_len < BUFFER_SIZE)
			break ;
		if (has_char(*out, 10) != -1)
			break ;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*out;

	out = 0;
	if (read(fd, 0, 0) < 0)
	{
		if (fd < 0 || fd > 1024)
			return (0);
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = 0;
		return (0);
	}
	ft_read(fd, &buffer[fd]);
	if (buffer[fd])
		ft_moise(&out, &buffer[fd]);
	if (!out)
	{
		free(buffer[fd]);
		buffer[fd] = 0;
	}
	return (out);
}
