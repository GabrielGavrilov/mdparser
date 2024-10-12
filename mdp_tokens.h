#ifndef __MDP_TOKENS_H__
#define __MDP_TOKENS_H__

typedef enum 
{
    TOKEN_EOF = -1,
    TOKEN_NEWLINE = 0,

    TOKEN_HASHTAG = 100,
    TOKEN_ASTERISK = 101,
    TOKEN_UNDERSCORE = 102,

    TOKEN_TEXT = 200
} TokenType;

typedef struct
{
    TokenType type;
    char* value;
} Token;


#endif