#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

// Simulating malloc failure by tracking the call count
static int malloc_fail_at = 0;
void *my_malloc(size_t size)
{
    static int malloc_call_count = 0;

    malloc_call_count++;

    // Simulate malloc failure after 'malloc_fail_at' calls
    if (malloc_call_count == malloc_fail_at)
        return NULL;

    return malloc(size);
}

// Replace the standard malloc with the simulated one for testing
#define malloc(size) my_malloc(size)

void test_get_next_line_with_malloc_failure(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Simulate malloc failure on the 3rd allocation (change for different tests)
    malloc_fail_at = 1;

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line: %s", line);
        free(line); // Don't forget to free the line!
    }

    close(fd);
}

int main()
{
    const char *filename = "123.txt";  // Replace with your test file

    // Run the test
    test_get_next_line_with_malloc_failure(filename);

    return 0;
}
