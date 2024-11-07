#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char *line;
	int fd;
	fd = open("m.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (strcmp(line, "exit\n") == 0)
		{
			free(line);
			close(0);
			break ;
		}
		printf("get_next_line: |%s", line);
		free(line);
	}
	// get_next_line(0);
}