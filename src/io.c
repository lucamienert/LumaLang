#include "include/io.h"
#include "include/misc.h"

char *get_file(char *filename)
{
    int len = strlen(filename);
    char *last_letters = &filename[len - 4];
    if(strcmp(last_letters, ".lcl") != 0) {
        LOG("File must end with '.lcl'");
        exit(2);
    }

    char *buffer = 0;
    size_t length;

    FILE *file = fopen(filename, "rb");
    if(!file)
    {
        LOG("Cannot open file");
        exit(2);
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = calloc(length, length);

    if(buffer)
        fread(buffer, 1, length, file);

    fclose(file);
    return buffer;
}