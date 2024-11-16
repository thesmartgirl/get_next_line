#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

static int read_line(int fd, char **saved)
{
	int bytes_read;
	char *buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if(!buff)
		return 1;
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*saved, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		if (bytes_read < 0)
		{
			free(buff);
			return 1;
		}
		buff[bytes_read] = '\0';
		*saved = gnl_strjoin(*saved, buff);
		if (*saved == NULL)
		{
			free(buff);
			return 1;
		}
	}
	free(buff);
	return 0;
}

static	char *extract_line(char **saved)
{
	char *line;
	int nl;
	char *temp;
	size_t line_len;

	nl = 0;
	while ((*saved)[nl] != '\n' && (*saved)[nl] != '\0')
		nl++;
	if (nl > 0 || (*saved)[0] == '\n')
		line = ft_substr(*saved, 0, nl+1);
	else
		line = NULL; //ft_strdup(*saved);
	line_len =  ft_strlen(line);
	temp = *saved;
	*saved = ft_substr(*saved, line_len, ft_strlen(*saved) - line_len);
	free(temp);
	return line;
}

char	*get_next_line(int fd)
{
    static char *saved;
		char *line;

		line = NULL;
		if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
			return (NULL);
		if (!saved)
			saved = ft_strdup("");
		if (!read_line(fd, &saved))
		{
				if (saved[0] == '\0')
				{
					free(saved);
					saved = NULL;
				}
				else
						line = extract_line(&saved);
		}
		else
    {
        free(saved);
				saved = NULL;
    }
		return line;
}
