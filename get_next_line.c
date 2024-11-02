#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *get_next_line(int fd) {
    size_t buffer_size = BUFFER_SIZE;
    size_t line_length = 0;
    char *line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!line)
        return NULL;

    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    line[0] = '\0';  // Initialize line

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer

        // Resize buffer if needed
        if (line_length + bytes_read >= buffer_size) {
            buffer_size *= 2;  // Increase buffer size
            char *new_line = resize_buffer(line, line_length, buffer_size + 1);
            if (!new_line) {
                free(line);  // Free in case of failure
                return NULL;
            }
            line = new_line;
        }

        // Append the buffer content to the line
        for (size_t i = 0; i < bytes_read; i++) {
            line[line_length++] = buffer[i];
        }

        // Check for newline
        if (strchr(buffer, '\n')) {
            break;
        }
    }

    // Null-terminate the final line
    line[line_length] = '\0';

    // Return NULL if no bytes were read and no line was accumulated
    if (line_length == 0 && bytes_read == 0) {
        free(line);
        return NULL;
    }

    return line;
}
