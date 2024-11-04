#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char    *get_next_line(int fd)
{
    char        *line;
    static char *buff;

    if (BUFFER_SIZE <= 0 || fd < 0)
        return (NULL);
    buf = get_buffer(fd, buff);
    if (!buf)
        return (NULL);
    line = get_line(buff);
    buf = get_remainder(buff);
    return (line);
}

char *get_line(char *buff)
{
  ssize_t bytes_read;
  char *nl;

  //join the buff with new read lines
  //look for new line
  //split on new line
  while (bytes_read > 0)
  {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    buff = ft_strjoin(buff, bytes_read);
    nl = ft_strch(buff, '\n'); //or 10
    if (nl)
    {
      line = ft_split(buff, '\n')[0];
    }
    //add bytes_read to line
    //if new line encountered return line
  }
  //retrun line or NULL
}

char  *get_remainder(char *buff)
{

}

char *get_next_line(int fd) {
    static char buffers[MAX_FD][BUFFER_SIZE];
    ssize_t bytes_read;

    while (bytes_read > 0)
    {
      bytes_read = read(fd, buffer, BUFFER_SIZE);

      //add bytes_read to line
      //if new line encountered return line
    }



//Use read() to fill the buffer for the fd if it doesn’t already contain a complete line.
//If there is leftover data from a previous call, concatenate it with the newly read data.



// If there is nothing else to read or if an error occurred, return NULL
// i.e. if read() returns 0 or -1
    if (bytes_read <= 0)
      return NULL;
    else
      return line;
}
