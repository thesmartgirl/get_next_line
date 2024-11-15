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
            break; // No more data, or error
        buff[bytes_read] = '\0';
        tmp = *draft;
        if (!*draft)
            *draft = ft_strdup(buff);
        else
            *draft = ft_strjoin(*draft, buff);
        free(tmp);
        if (ft_strchr(*draft, '\n'))
            break;
    }
		return 0;
}

static char	*extract_line(char *draft)
{
    int i = 0;

    if (ft_strchr(draft, '\n'))
    {
        while (draft[i] != '\n')
            i++;
        return (ft_substr(draft, 0, i + 1)); // Extract line including newline
    }
    return (ft_strdup(draft)); // Return entire draft if no newline
}

char	*get_next_line(int fd)
{
    static char	*drafts[FOPEN_MAX];
    char *line;
    char *tmp;
    char *buff;

    if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
        return (NULL); // Invalid buffer size or file descriptor

    buff = (char *)malloc(BUFFER_SIZE + 1);
    if (!buff)
        return (NULL); // Memory allocation failure

    if(!read_line(fd, &drafts[fd], buff))
		{
			free(buff);
			return NULL;
		}
		else
		{
	    if (!drafts[fd] || drafts[fd][0] == '\0')
	    {
	        free(buff);
	        return (NULL); // No data or empty file
	    }
	    line = extract_line(drafts[fd]);
	    tmp = drafts[fd];
	    size_t remaining_len = ft_strlen(drafts[fd]) - ft_strlen(line);
	    drafts[fd] = ft_substr(drafts[fd], ft_strlen(line), remaining_len);
	    free(tmp);
			free(buff);
		}
	  return (line);
}
