/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_single.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:58:05 by asadik            #+#    #+#             */
/*   Updated: 2026/01/23 17:41:29 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_utils.h"

static char	*eof_or_error(t_buffer *buffer, char *next_line)
{
	if (buffer->bytes_read == 0)
		return (next_line);
	else
	{
		free(next_line);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	char			*next_line;
	size_t			line_len;

	if (BUFFER_ERROR || fd < 0)
		return (NULL);
	next_line = NULL;
	line_len = 0;
	while (1)
	{
		if (buffer.cursor == 0)
			buffer.bytes_read = read(fd, buffer.content, BUFFER_SIZE);
		if (buffer.bytes_read <= 0)
			return (eof_or_error(&buffer, next_line));
		while (buffer.cursor < buffer.bytes_read)
		{
			if (!append(&next_line, buffer.content[buffer.cursor], ++line_len))
				return (NULL);
			buffer.cursor++;
			if (buffer.content[buffer.cursor - 1] == '\n')
				return (next_line);
		}
		buffer.cursor = 0;
	}
	return (next_line);
}
