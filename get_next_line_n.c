#include <unistd.h>
#include <stdlib.h>

static void read_line (int fd, char **drafts)
{
  char *buff;
  int bytes_read;

  bytes_read = 1;
  while(bytes_read > 0 && !ft_strchr(drafts[fd], '\n'))
  {
    buff = (char *)malloc(BUFFER_SIZE+1);
    if (!buff)
      return; //PLZ UPDATE ME
    bytes_read = read(fd, buff, BUFFER_SIZE);
    if (bytes_read == -1) {
            free(buff);
            return; // Handle read failure
    }
    buff[bytes_read] = '\0';
    if (!drafts[fd]) //first try not used before, == NULL
      drafts[fd] = ft_strdup(buff);
    else
      drafts[fd] = ft_strjoin(drafts[fd], buff); //this uses malloc
    free(buff);
  }
}

static char *extract_line(int fd, char **drafts)
{
  char *line;
  char *nl;
  char *tmp;

  nl = ft_strchr(drafts[fd], '\n');
  if(ft_strchr(drafts[fd], '\n')) //new line exists in drafts
  {
    line = ft_substr(drafts[fd], 0, nl - drafts[fd] + 1); //this usese malloc
    tmp = drafts[fd];
    drafts[fd] = ft_substr(drafts[fd], nl + 1, (ft_strlen(drafts[fd])
      - ft_strlen(nl))); //this uses malloc
    free(tmp);
  }
  else
  {
    //nl not found in drafts
    line = ft_strdup(drafts[fd]);
    free(drafts[fd]);
    drafts[fd] = NULL;
  }
  return line;
}

// drafts is  not initialized!! --> no need static vars are auto-initialized to NULL
char    *get_next_line(int fd)
{
    static char *drafts[FOPEN_MAX];

    if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
        return (NULL);
    read_line(fd, drafts);
    if (!drafts[fd] || drafts[fd][0] == '\0') {
        return NULL; // No more data to read
    }
    return(extract_line(fd, drafts));
}
