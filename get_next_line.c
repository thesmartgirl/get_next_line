#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

static int read_line(int fd, char **saved)
{
	int bytes_read;
	char *buff;

	// if(*saved)
	// 	printf("*saved is true\n");
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
	// printf("freeing buff in read_line\n");
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
		size_t line_len;

		line = NULL;
		if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
			return (NULL);
		if (!saved)
			saved = ft_strdup("");
		if (!read_line(fd, &saved))
		{
			printf("I'm here1\n");

				if (saved[0] != '\0')
				{
					line = extract_line(saved);
					temp = saved;
					line_len = ft_strlen(line);
					updated_len =  ft_strlen(saved) - line_len;
					saved = ft_substr(saved, line_len, updated_len);
					printf("saved len = %ld\n", ft_strlen(saved));
					if(ft_strlen(saved) == 0)
						free(saved);
					free(temp);
				}
		}
		else
		{
				printf("I'm here\n");
				free(saved);
			}
		 return line;
}
