#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

// Function to extract a line from the saved data
char *extract_line(char **saved_data)
{
    size_t i;
		char *line;

		i = 0;
    while ((*saved_data)[i] != '\n' && (*saved_data)[i] != '\0')
        i++;
		if (i == 0)
			line = ft_strdup((*saved_data));
		else
		  line = ft_substr((*saved_data), 0, i+1);
    return line;
}

// Function to update the static data (saved_data) after extracting a line
void update_saved_data(char **saved_data)
{
    size_t i;
		size_t j;

		i = 0;
    while ((*saved_data)[i] != '\n' && (*saved_data)[i] != '\0')
        i++;
    if ((*saved_data)[i] == '\0')
    {
        free(*saved_data); // Free only if saved_data is not NULL
        *saved_data = NULL;
    }
    else
    {
				j = 0;
        char *new_data = (char *)malloc(ft_strlen(*saved_data) - i);
        if (!new_data)
            return; // Should handle this case more gracefully
        i++; // Skip the newline character
        while ((*saved_data)[i])
            new_data[j++] = (*saved_data)[i++];
        new_data[j] = '\0';
        free(*saved_data);
        *saved_data = new_data;
    }
}

// Main get_next_line function
char *get_next_line(int fd)
{
    static char *saved_data = NULL;
		ssize_t bytes_read;
		char *line;
		char *buff;
		char *temp;

		buff = (char *)malloc(BUFFER_SIZE + 1);
    if (!buff || fd < 0)
        return NULL;

    // Read more data into saved_data if necessary
    while (!saved_data || !ft_strchr(saved_data, '\n'))
    {
        bytes_read = read(fd, buff, BUFFER_SIZE);
        if (bytes_read <= 0) // No more data to read
        {
						free(buff);
						return NULL; // No more lines to return
			  }
        buff[bytes_read] = '\0'; // Null-terminate the buffer
        temp = saved_data;
        saved_data = ft_strjoin(saved_data, buff); // Append new data to saved_data
        free(temp);
        if (!saved_data)
        {
            free(buff);
            return NULL; // Memory allocation failure
        }
    }

    free(buff);

    // Extract the line from saved_data
    line = extract_line(&saved_data);
    if (!line)
        return NULL;

    // Update saved_data to remove the extracted line
    update_saved_data(&saved_data);

    return line;
}
/*
int main()
{
    int fd = open("sample.txt", O_RDONLY);  // Replace with an actual file
    if (fd < 0)
    {
        perror("Failed to open file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Print the line (doesn't need to include newline)
        free(line);  // Don't forget to free each line after use
    }

    close(fd);
    return 0;
}*/
