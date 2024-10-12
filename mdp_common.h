#ifndef __MDP_COMMON_H__
#define __MDP_COMMON_H__

#include "mdparser.h"

typedef int (*FIND_CHAR)(char* str, char c);

typedef struct 
{
    FILE* fileptr;
    int size;
    char* buffer;
} MDPFile;

char* substr(char* str, int start, int end);
int find_char_pos(char* str, char c, FIND_CHAR find);
int first(char* str, char c);
int last(char* str, char c);
void cat(char** first_str, char* second_str);
MDPFile* open_file(char* name);
void write_to_file(MDPFile* file, char* buffer);

#endif