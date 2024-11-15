/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataan <ataan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:28:19 by ataan             #+#    #+#             */
/*   Updated: 2024/11/14 20:15:58 by ataan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	read_line(int fd, char **draft, char *buff)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			return 1;
		buff[bytes_read] = '\0';
		if (!*draft) // first try not used before, == NULL
			*draft = ft_strdup(buff);
		else
			*draft = ft_strjoin(*draft, buff);
		if (ft_strchr(*draft, '\n'))
			break ;
	}
	return 0;
}

static char	*extract_line(char *draft)
{
  int i;

  i = 0;
  if (ft_strchr(draft, '\n'))
  {
	while (draft[i] != '\n')
  		i++;
	return(ft_substr(draft, 0, i + 1));
  }
  return (ft_strdup(draft));
}

char	*get_next_line(int fd)
{
	static char	*drafts[FOPEN_MAX];
	char *line;
	char *tmp;
	char *buff;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
			return NULL;
	if (!read_line(fd, &drafts[fd], buff))
		return (NULL); // No more data to read
	line = extract_line(drafts[fd]);
	tmp = drafts[fd];
	drafts[fd] = ft_substr(drafts[fd], ft_strlen(line), (ft_strlen(drafts[fd])
						- ft_strlen(line)));
	free(tmp);
	free(buff);
	return (line);
}
