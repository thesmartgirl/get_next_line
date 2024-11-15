#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// Function to find the length of a string
size_t ft_strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

// Function to duplicate a string
char *ft_strdup(const char *s)
{
    size_t len = ft_strlen(s);
    char *dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

// Function to join two strings
char *ft_strjoin(char *s1, const char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *joined = (char *)malloc(len1 + len2 + 1);
    if (!joined)
        return NULL;
    for (size_t i = 0; i < len1; i++)
        joined[i] = s1[i];
    for (size_t i = 0; i < len2; i++)
        joined[len1 + i] = s2[i];
    joined[len1 + len2] = '\0';
    return joined;
}

// Function to extract a line from the saved data
char *extract_line(char **saved_data)
{
    size_t i = 0;
    while ((*saved_data)[i] != '\n' && (*saved_data)[i] != '\0')
        i++;
    char *line = (char *)malloc(i + 2); // +1 for newline and +1 for null terminator
    if (!line)
        return NULL;
    for (size_t j = 0; j < i + 1; j++) // Include newline if present
        line[j] = (*saved_data)[j];
    line[i + 1] = '\0';
    return line;
}

// Function to update the static data (saved_data) after extracting a line
void update_saved_data(char **saved_data)
{
    size_t i = 0;
    while ((*saved_data)[i] != '\n' && (*saved_data)[i] != '\0')
        i++;
    if ((*saved_data)[i] == '\0')
    {
        free(*saved_data);
        *saved_data = NULL;
    }
    else
    {
        size_t j = 0;
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
    char *buff = (char *)malloc(BUFFER_SIZE + 1);
    if (!buff || fd < 0)
        return NULL;

    // Read more data into saved_data if necessary
    while (!saved_data || !strchr(saved_data, '\n'))
    {
        ssize_t bytes_read = read(fd, buff, BUFFER_SIZE);
        if (bytes_read <= 0) // No more data to read
        {
            free(buff);
            if (!saved_data)
                return NULL; // No more lines to return
            break; // EOF reached or read error, we still have data to process
        }
        buff[bytes_read] = '\0'; // Null-terminate the buffer
        char *temp = saved_data;
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
    char *line = extract_line(&saved_data);
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
