#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

static int read_line(int fd, char *buff, char **saved)
{
	int bytes_read;
	// char *temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == 0) { //empty file or EOF
			break;
		}
		if (bytes_read < 0) { //error reading
			printf("bytes_read < 0\n" );
			free(*saved);
			return 1;
		}
		buff[bytes_read] = '\0';
		// temp = *saved;
		*saved = ft_strjoin(*saved, buff);
		// free(temp);
	}
	return 0;
}

static	char *extract_line(const char *saved)
{
	char *line;
	int nl;

	nl = 0;
	while (saved[nl] != '\0' && saved[nl] != '\n')
		nl++;

	if (nl > 0 || saved[0] == '\n')
		line = ft_substr(saved, 0, nl+1);
	else
		line = ft_strdup(saved);

	return line;
}

static	char *update_saved( char *saved, const size_t line_len)
{
	char *updated;
	size_t updated_len;

	updated_len =  ft_strlen(saved) - line_len;
	if (updated_len <= 0)
	{
		if (saved)
		{
			free(saved);
		}
		return NULL;
	}
	updated = ft_substr(saved, line_len, updated_len);
	return updated;
}

char	*get_next_line(int fd)
{
    static char *saved = NULL;
		char *line;
		char *buff;
		char *temp;

		buff = (char *)malloc(BUFFER_SIZE + 1);
		if(!buff)
			return NULL;

		line = NULL;
		if (!saved)
			saved = ft_strdup("");
		if (!ft_strchr(saved, '\n'))
    	if (!read_line(fd, buff, &saved))
			{
				if (ft_strlen(saved) > 0)
				{
					line = extract_line(saved);
					temp = saved;
					saved = update_saved(saved, ft_strlen(line));
					free(temp);
				}
			}
		free(buff);
    return line;
}
