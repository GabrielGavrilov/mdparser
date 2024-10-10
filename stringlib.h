#ifndef __STRINGLIB_H__
#define __STRINGLIB_H__

#include "mdparser.h"

typedef int (*FIND_CHAR)(char* str, char c);

char* substr(char* str, int start, int end);
int find_char_pos(char* str, char c, FIND_CHAR find);
int first(char* str, char c);
int last(char* str, char c);
void cat(char** first_str, char* second_str);

#endif