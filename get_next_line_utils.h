/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:29:49 by asadik            #+#    #+#             */
/*   Updated: 2026/02/02 16:07:56 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H
# define BUFFER_ERROR 0
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# if BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  undef BUFFER_ERROR
#  define BUFFER_SIZE 1
#  define BUFFER_ERROR 1
# endif
# include <stdlib.h>

typedef struct s_buffer
{
	int		cursor;
	int		bytes_read;
	char	content[BUFFER_SIZE];
}			t_buffer;

typedef struct s_list
{
	int				fd;
	t_buffer		*content;
	struct s_list	*next;
}					t_list;

char		*get_next_line_mul(int fd);
int			append(char **next_line, char c, size_t len);
t_buffer	*get_buffer(int fd, t_list **list);
t_list		*new_node(int fd);
void		free_node(int fd, t_list **list);
void		free_all_nodes(t_list *list);

#endif
