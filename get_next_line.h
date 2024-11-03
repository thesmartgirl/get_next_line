#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //plz remove before submission

#define BUFFER_SIZE 3
#define MAX_FD 1024

char *get_next_line(int fd);

#endif
