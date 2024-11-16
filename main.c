#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// int	main(void)
// {
// 	char *line;
// 	int fd;
// 	fd = open("m.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		if (strcmp(line, "exit\n") == 0)
// 		{
// 			free(line);
// 			close(0);
// 			break ;
// 		}
// 		printf("get_next_line: |%s", line);
// 		free(line);
// 	}
// 	// get_next_line(0);
// }

int	main(void)
{
	int		fd1;
	char	*line;


	// line = get_next_line(-1);
	// printf("get_next_line: |%s", line);
	// free(line);
	// line = get_next_line(100);
	// printf("get_next_line: |%s", line);
	// free(line);
	fd1 = open("empty", O_RDONLY);
	line = get_next_line(fd1);
	printf("get_next_line: |%s", line);
	free(line);
	line = get_next_line(fd1);
	printf("get_next_line: |%s", line);
			free(line);
			line = get_next_line(fd1);
			printf("get_next_line: |%s", line);
					free(line);

	close(fd1);
	return (0);
}

/*
int	main(void)
{
	int fd1, fd3;
	char *line;

	fd1 = open("file1.txt", O_RDWR);
	if (fd1 == -1) {
		perror("Error opening file3.txt");
		return (1);
	}

	fd3 = open("file3.txt", O_RDWR);
		// Or any other file where you want to write
	if (fd3 == -1) {
		perror("Error opening file3.txt for writing");
		close(fd1);
		return (1);
	}

	// Read a line from fd1 and write to fd3
	line = get_next_line(fd1);
	if (line != NULL) {
		write(fd3, line, 6);  // Write the first 5 characters of the line to fd3
		free(line);  // Free the allocated memory
	}

	// Close the file descriptors
	close(fd1);
	close(fd3);

	return (0);
}*/
