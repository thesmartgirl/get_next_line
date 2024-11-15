static char *read_line(int fd, char **draft, char *buff)
{
    int bytes_read;
    char *tmp;

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buff, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            return (NULL);
        }
        buff[bytes_read] = '\0';
        tmp = *draft;
        if (!*draft)
            *draft = ft_strdup(buff);
        else
            *draft = ft_strjoin(*draft, buff);
        free(tmp);
        if (ft_strchr(*draft, '\n'))
            break;
    }
    return *draft;
}

static char *extract_line(char *draft)
{
    int i = 0;
    while (draft[i] != '\0')
    {
        if (draft[i] == '\n')
            return(ft_substr(draft, 0, i + 1));
        i++;
    }
    return (ft_strdup(draft));
}

char *get_next_line(int fd)
{
    static char *draft;
    char *line;
    char *tmp;
    char *buff;
    size_t len_remaining;

    if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
        return (NULL);

    buff = (char *)malloc(BUFFER_SIZE + 1);
    if (!buff)
        return NULL;

    draft = read_line(fd, &draft, buff);
    if (!draft)
    {
        free(buff);
        return (NULL); // No more data to read
    }

    line = extract_line(draft);

    tmp = draft;
    len_remaining = ft_strlen(draft) - ft_strlen(line);
    draft = ft_substr(tmp, ft_strlen(line), len_remaining);

    free(tmp);
    free(buff);

    return (line);
}
