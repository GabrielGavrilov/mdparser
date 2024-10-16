#include "mdp_common.h"

char* substr(char* str, int start, int end)
{
    int size = end - start;
    char* new_str = (char*)malloc(size);
    
    memcpy(new_str, str+start, size);
    *(new_str + size) = 0;
    
    return new_str;
}

int find_char_pos(char* str, char c, FIND_CHAR find) 
{
    return find(str, c);
}

int first(char* str, char c)
{
    int pos = 0;
    
    while(*str) 
    {
        if(*str == c)
        {
            return pos;
        }

        pos++;
        *str++;
    }

    return -1;
}

int last(char* str, char c)
{
    int len = strlen(str);
    int pos = len;
    str = (str+len-1);

    while(*str)
    {
        if(*str == c)
        {
            return pos;
        }

        pos--;
        *str--;
    }

    return -1;
}

void cat(char** first_str, char* second_str)
{
    int size = (strlen(*first_str) + strlen(second_str));
    char* catstr = (char*)malloc(sizeof(char)*(size + 1));

    memcpy(catstr, *first_str, strlen(*first_str));
    memcpy(catstr + strlen(*first_str), second_str, strlen(second_str));

    *(catstr + size + 1) = 0;
    *first_str = catstr;
}

int get_file_length(FILE* file)
{
    int length = 0;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    return length;
}

MDPFile* open_file(char* name)
{
    MDPFile* file = (MDPFile*)malloc(sizeof(MDPFile));
    FILE* fptr;
    
    fptr = fopen(name, "rb");

    if(!fptr)
        fptr = fopen(name, "wb");

    int length = get_file_length(fptr);
    
    char* buffer = (char*)malloc(length * sizeof(char) + 1);
    fread(buffer, sizeof(char), length, fptr);
    buffer[length] = 0;

    file->fileptr = fptr;
    file->size = length;
    file->buffer = buffer;

    return file; 
}

void write_to_file(MDPFile* file, char* buffer)
{
    fwrite(buffer, strlen(buffer), sizeof(char), file->fileptr);
    fclose(file->fileptr);
}