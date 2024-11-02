char *resize_buffer(char *old_buffer, size_t old_size, size_t new_size) {
    char *new_buffer = malloc(new_size);
    if (!new_buffer)
        return NULL;
    for (size_t i = 0; i < old_size; i++) {
        new_buffer[i] = old_buffer[i];  // Copy old data to new buffer
    }
    free(old_buffer);  // Free old buffer
    return new_buffer;
}
