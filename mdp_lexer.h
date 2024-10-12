#ifndef __MDP_LEXER_H__
#define __MDP_LEXER_H__

#include "mdparser.h"
#include "mdp_tokens.h"
#include "mdp_common.h"

typedef struct
{
    int src_size;
    int curr_pos;
    const char* src;
    char curr_char;
} Lexer;

Lexer* init_lexer(const char* src);
void free_lexer(Lexer* lexer);
void advance_lexer(Lexer* lexer);
char peek_lexer(Lexer* lexer);
Token get_next_token(Lexer* lexer);

#endif