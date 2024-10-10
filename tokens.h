#ifndef __TOKENS_H__
#define __TOKENS_H__

typedef enum 
{
    TOKEN_EOF = -1,
    TOKEN_NEWLINE = 0,

    TOKEN_HASHTAG = 100,

    TOKEN_TEXT = 200
} TokenType;

typedef struct
{
    TokenType type;
    char* value;
} Token;


#endif