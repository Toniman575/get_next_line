/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_mul.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:58:05 by asadik            #+#    #+#             */
/*   Updated: 2026/01/23 17:41:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_utils.h"

static char	*eof_or_error(t_buffer *buf, char *nex_l, int fd, t_list **buf_lis)
{
	if (buf->bytes_read == 0)
	{
		free_node(fd, buf_lis);
		return (nex_l);
	}
	else
	{
		free_node(fd, buf_lis);
		free(nex_l);
		return (NULL);
	}
}

static t_buffer	*init(int fd, t_list **buf_lis, char **nex, size_t *len)
{
	*nex = NULL;
	*len = 0;
	if (fd == -2)
		return (free_all_nodes(*buf_lis), NULL);
	else if (BUFFER_SIZE <= 0 || fd <= 0)
		return (NULL);
	return (get_buffer(fd, buf_lis));
}

/// If this function is called with fd defined as -2 it will free
/// all allocated memory in buffer_list. Otherwise it will only free
/// nodes in the linked list that correspond to fd that have reached EOF.
char	*get_next_line_mul(int fd)
{
	static t_list	*buffer_list;
	char			*next_line;
	size_t			line_len;
	t_buffer		*buffer;

	buffer = init(fd, &buffer_list, &next_line, &line_len);
	while (buffer)
	{
		if (buffer->cursor == 0)
			buffer->bytes_read = read(fd, buffer->content, BUFFER_SIZE);
		if (buffer->bytes_read <= 0)
			return (eof_or_error(buffer, next_line, fd, &buffer_list));
		while (buffer->cursor < buffer->bytes_read)
		{
			line_len++;
			if (!append(&next_line, buffer->content[buffer->cursor], line_len))
				return (free_node(fd, &buffer_list), NULL);
			buffer->cursor++;
			if (buffer->content[buffer->cursor - 1] == '\n')
				return (next_line);
		}
		buffer->cursor = 0;
	}
	return (next_line);
}
