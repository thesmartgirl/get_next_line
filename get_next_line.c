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

static void	read_line(int fd, char **draft)
{
	char	*buff;
	int		bytes_read;
	char	*tmp;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return ;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free(buff));
		buff[bytes_read] = '\0';
		tmp = *draft;
		if (!*draft) // first try not used before, == NULL
			*draft = ft_strdup(buff);
		else
			*draft = ft_strjoin(*draft, buff);
		free(tmp);
		if (ft_strchr(*draft, '\n'))
			break ;
	}
	free(buff);
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

// static char	*extract_line(int fd, char *drafts)
// {
// 	char	*line;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (ft_strchr(drafts[fd], '\n')) // new line exists in drafts
// 	{
// 		while (drafts[fd][i] != '\n')
// 			i++;
// 		line = ft_substr(drafts[fd], 0, i + 1); // this usese malloc
// 		tmp = drafts[fd];
// 		drafts[fd] = ft_substr(drafts[fd], i + 1, (ft_strlen(drafts[fd])
// 					- ft_strlen(line))); // this uses malloc
// 		free(tmp);
// 	}
// 	else // nl not found in drafts
// 	{
// 		line = ft_strdup(drafts[fd]);
// 		free(drafts[fd]);
// 		drafts[fd] = NULL;
// 	}
// 	return (line);
// }

char	*get_next_line(int fd)
{
	static char	*drafts[FOPEN_MAX];
	char *line;
	char *tmp;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	read_line(fd, &drafts[fd]);
	if (!drafts[fd] || drafts[fd][0] == '\0')
		return (NULL); // No more data to read
	line = extract_line(drafts[fd]);
	tmp = drafts[fd];
	drafts[fd] = ft_substr(drafts[fd], ft_strlen(line), (ft_strlen(drafts[fd])
						- ft_strlen(line)));
	free(tmp);
	return (line);
}
