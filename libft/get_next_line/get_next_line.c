/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:02:01 by toandrad          #+#    #+#             */
/*   Updated: 2025/07/04 15:19:27 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_nl(int fd, char *c_left, char *buffer);
static char	*split_line(char *line);

char	*get_next_line(int fd)
{
	static char	*c_left;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(c_left);
		c_left = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(c_left);
		c_left = NULL;
		return (NULL);
	}
	line = read_until_nl(fd, c_left, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	c_left = split_line(line);
	return (line);
}

static char	*read_until_nl(int fd, char *c_left, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(c_left);
			return (NULL);
		}
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!c_left)
			c_left = ft_strdup("");
		tmp = c_left;
		c_left = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (c_left);
}

static char	*split_line(char *line_buffer)
{
	ssize_t	i;
	char	*c_left;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	c_left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*c_left == 0)
	{
		free(c_left);
		c_left = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (c_left);
}
