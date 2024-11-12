#include <unistd.h>
#include <stdlib.h>

static void read_line (int fd, char **drafts)
{
  char *buff;
  int bytes_read;

  bytes_read = 1;
  while(bytes_read > 0 && gnl_strchr(drafts[fd], '\n') < 0)
  {
    buff = (char *)malloc(BUFFER_SIZE+1);
    if (!buff)
      return; //PLZ UPDATE ME
    bytes_read = read(fd, buff, BUFFER_SIZE);
    buff[bytes_read] = '\0';
    drafts[fd] = ft_strjoin(drafts[fd], buff); //this uses malloc
    free(buff);
  }
}

static char *extract_line(int fd, char **drafts)
{
  char *line;
  int nl;

  nl = gnl_strchr(drafts[fd], '\n')
  if(nl >= 0)
  {
    line = ft_substr(drafts[fd], 0, nl + 1); //this usese malloc
    drafts[fd] = ft_substr(drafts[fd], nl + 1, ft_strlen(drafts[fd]) - nl); //this uses malloc
  }
  else
  {
    //nl not found in drafts
    line = drafts[fd];
    free(drafts[fd]);
  }
  return line;
}

// drafts is  not initialized!!
char    *get_next_line(int fd)
{
    static char *drafts[FD_MAX_OPEN];

    if (BUFFER_SIZE <= 0 || fd < 0)
        return (NULL);
    read_line(fd, drafts);
    return(extract_line(fd, drafts));
}
