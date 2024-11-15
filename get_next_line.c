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

static char	*read_line(int fd, char **draft, char *buff)
{
	int		bytes_read;
	char 	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if(draft)
				free(draft);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		tmp = *draft;
		if (!*draft) // first try not used before, == NULL
			*draft = ft_strdup(buff);
		else
			*draft = ft_strjoin(*draft, buff);
		free(tmp);
		// printf("read_line draft = %s\n", *draft);
		if (ft_strchr(*draft, '\n'))
			break ;
	}
	return draft;
}

static char	*extract_line(char *draft)
{
  int i;

  i = 0;
  while (draft[i] != '\0')
  {
		// printf("draft[i] = %c, ", draft[i]);
		if (draft[i] == '\n')
			return(ft_substr(draft, 0, i + 1));
	  i++;
	 }
  return (ft_strdup(draft));
}

char	*get_next_line(int fd)
{
	static char	*draft;
	char *line;
	char *tmp;
	char *buff;
	size_t len_remaining;

	// 1- allocate buffer
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
			return NULL;

	//2- read line
	draft = read_line(fd, &draft, buff);
	if (!draft)
	{
		free(buff);
		return (NULL); // No more data to read
	}

	//3- extract line
	line = extract_line(draft);

	//4- update static variable for next call
	tmp = draft;
	len_remaining = (ft_strlen(draft) - ft_strlen(line));
	draft = ft_substr(draft, ft_strlen(line), len_remaining);

	//5- Free Resources
	free(tmp);
	free(buff);
	// printf("draft = %s\n", draft);
	// printf("line = %s\n", line);
	return (line);
}
