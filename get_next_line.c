/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:27:42 by ataan             #+#    #+#             */
/*   Updated: 2024/11/12 17:49:58 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static char *cleanup(char **line_draft, int fd)
{
	free(line_draft[fd]);
	line_draft[fd] = NULL;
	return NULL;
}
static char	*extract_line(char **line_draft, int fd)
{
	char	*tmp;
	char	*line;
	int		i;

	if (!line_draft[fd])
		return (NULL);
	tmp = line_draft[fd];
	i = ft_strchr(line_draft[fd], '\n');
	if (i == -1)
	{
		if (ft_strlen(line_draft[fd]) == 0)
			return (cleanup(line_draft, fd));
		line = ft_strdup(line_draft[fd]);
		return (free(line_draft[fd]), line_draft[fd] = NULL, line);
	}
	line = ft_substr(tmp, 0, i + 1);
	if (line == NULL)
		return (free(line_draft[fd]), line_draft[fd] = NULL, NULL);
	line_draft[fd] = ft_substr(tmp, i + 1, (ft_strlen(tmp) - i));
	return (free(tmp), line);
}

static char	*read_line(char *buff, char **line_draft, int fd)
{
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (ft_strchr(line_draft[fd], '\n') == -1)
		{
			buff = (char *)malloc(BUFFER_SIZE + 1);
			if (buff == NULL)
				return (free(line_draft[fd]), line_draft[fd] = NULL, NULL);
			bytes_read = read(fd, buff, BUFFER_SIZE);
			if (bytes_read == -1)
				return (free(buff), free(line_draft[fd]), line_draft[fd] = NULL,
					NULL);
			buff[bytes_read] = '\0';
			line_draft[fd] = ft_strjoin(line_draft[fd], buff);
			free(buff);
		}
		else
			return (extract_line(line_draft, fd));
	}
	return (extract_line(line_draft, fd));
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*line_draft[FOPEN_MAX];
	char *line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (line_draft[fd] == NULL)
		line_draft[fd] = ft_strdup("");
	buff = NULL;
	line = read_line(buff, line_draft, fd);
	// printf("returning line = %s\n", line );
	return(line);
}
