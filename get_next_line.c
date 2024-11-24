/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:27:42 by ataan             #+#    #+#             */
/*   Updated: 2024/11/24 11:47:45 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	cleanup_fd(char **line_draft)
{
	if (line_draft[0])
	{
		free(line_draft[0]);
		line_draft[0] = NULL;
	}
}

static char	*extract_line(char **line_draft)
{
	char	*line;
	int		nl;

	if (!line_draft[0])
		return (NULL);
	nl = 0;
	while (line_draft[0][nl] != '\n' && line_draft[0][nl] != '\0')
		nl++;
	if (nl == 0 && line_draft[0][0] != '\n')
	{
		if (ft_strlen(line_draft[0]) == 0)
			line = NULL;
		else
			line = ft_strdup(line_draft[0]);
		cleanup_fd(line_draft);
		return (line);
	}
	line = ft_substr(line_draft[0], 0, nl + 1);
	if (line == NULL)
	{
		cleanup_fd(line_draft);
		return (NULL);
	}
	return (line);
}

static char	*update_line_draft(char **line_draft, char *line)
{
	char	*tmp;

	tmp = line_draft[0];
	line_draft[0] = ft_substr(tmp, ft_strlen(line), (ft_strlen(line_draft[0])
				- ft_strlen(line)));
	free(tmp);
	return (line_draft[0]);
}

static char	*read_line(char *buff, char **line_draft, int fd)
{
	int	bytes_read;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
	{
		cleanup_fd(line_draft);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(line_draft[0], '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			cleanup_fd(line_draft);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = '\0';
		line_draft[0] = ft_strjoin(line_draft[0], buff);
	}
	free(buff);
	return ("OK");
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*line_draft[1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (line_draft[0] == NULL)
		line_draft[0] = ft_strdup("");
	buff = NULL;
	if (read_line(buff, line_draft, fd))
	{
		line = extract_line(line_draft);
		line_draft[0] = update_line_draft(line_draft, line);
	}
	if (ft_strlen(line_draft[0]) == 0)
		cleanup_fd(line_draft);
	return (line);
}
