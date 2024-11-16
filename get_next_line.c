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
	}
	free(buff);
	return 0;
}

static	char *extract_line(const char *saved)
{
	char *line;
	int nl;

	nl = 0;
	while (saved[nl] != '\n' && saved[nl] != '\0')
		nl++;
	if (nl > 0 || saved[0] == '\n')
		line = ft_substr(saved, 0, nl+1);
	else
		line = ft_strdup(saved);
	return line;
}

// static	char *update_saved(char *saved, const size_t line_len)
// {
// 	char *updated;
// 	size_t updated_len;
//
// 	updated_len =  ft_strlen(saved) - line_len;
// 	if (updated_len <= 0)
// 	{
// 		// free(saved);
// 		updated = NULL;
// 	}
// 	else
// 		updated = ft_substr(saved, line_len, updated_len);
// 	// free(saved);
// 	return updated;
// }

char	*get_next_line(int fd)
{
    static char *saved;
		char *line;
		char *temp;
		size_t updated_len;

		line = NULL;
		if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
			return (NULL);
		if (!saved)
			saved = ft_strdup("");
		if (!read_line(fd, &saved) && saved[0] != '\0')
		{
				// if (saved[0] == '\0')
				// {
				// 	free(saved);
				// 	saved = NULL;
				// }
				// else
				{
						line = extract_line(saved);
						updated_len =  ft_strlen(saved) - ft_strlen(line);
            {
								temp = saved;
                saved = ft_substr(saved, ft_strlen(line), updated_len);
								free(temp);
            }
				}
		}
		// else
    {
        free(saved);
				saved = NULL;
    }
		return line;
}
