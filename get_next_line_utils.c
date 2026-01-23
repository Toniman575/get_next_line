/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:33:50 by asadik            #+#    #+#             */
/*   Updated: 2026/01/23 15:22:39 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

int	append(char **next_line, char c, size_t len)
{
	char	*temp;
	int		i;

	if (*next_line != NULL)
	{
		temp = malloc((len + 1) * sizeof(char));
		if (!temp)
			return (free(*next_line), 0);
		i = 0;
		while ((*next_line)[i] != '\0')
		{
			temp[i] = (*next_line)[i];
			i++;
		}
		free(*next_line);
		*next_line = temp;
	}
	else
		*next_line = malloc((len + 1) * sizeof(char));
	if (!*next_line)
		return (0);
	(*next_line)[len - 1] = c;
	(*next_line)[len] = '\0';
	return (1);
}

t_list	*new_node(int fd)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->content = malloc(sizeof(t_buffer));
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->content->bytes_read = 0;
	node->content->cursor = 0;
	node->content->content[0] = '\0';
	node->next = NULL;
	return (node);
}

t_buffer	*get_buffer(int fd, t_list **list)
{
	t_list	*current;

	if (!(*list))
	{
		current = new_node(fd);
		if (!current)
			return (NULL);
		*list = current;
	}
	else
		current = *list;
	while (current->fd != fd)
	{
		if (current->next)
			current = current->next;
		else
		{
			current->next = new_node(fd);
			if (!current->next)
				return (NULL);
			current = current-> next;
		}
	}
	return (current->content);
}

void	free_node(int fd, t_list **list)
{
	t_list	*current;
	t_list	*next;

	if (*list)
	{
		current = *list;
		if (current->fd == fd)
		{
			*list = current->next;
			free(current->content);
			free(current);
		}
		else
		{
			next = current->next;
			while (current->next->fd != fd && current->next)
			{
				current = next;
				next = current->next;
			}
			current->next = next->next;
			free(next->content);
			free(next);
		}
	}
}

void	free_all_nodes(t_list *list)
{
	t_list	*next;

	if (list)
	{
		next = list->next;
		while (next)
		{
			next = list->next;
			free(list->content);
			free(list);
			list = next;
			next = list->next;
		}
		free(list->content);
		free(list);
	}
}