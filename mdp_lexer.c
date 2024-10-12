#include "mdp_lexer.h"

Lexer* init_lexer(const char* src)
{
    cat(&src, "\n");
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));

    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->curr_pos = -1;

    advance_lexer(lexer);
    return lexer;
}

void free_lexer(Lexer* lexer)
{
    free(lexer);
    lexer->src = NULL;
    lexer = NULL;
}

void advance_lexer(Lexer* lexer)
{
    lexer->curr_pos++;

    if(lexer->curr_pos >= lexer->src_size)
        lexer->curr_char = '\0';
    
    else
        lexer->curr_char = lexer->src[lexer->curr_pos];
}

char peek_lexer(Lexer* lexer)
{
    if(lexer->curr_pos + 1 >= lexer->src_size)
        return '\0';

    return lexer->src[lexer->curr_pos + 1];
}

void skip_whitespace(Lexer* lexer)
{
    while(lexer->curr_char == ' ' || lexer->curr_char == '\t')
        advance_lexer(lexer);
}

Token create_token(char* value, TokenType type)
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

Token create_text_token(Lexer* lexer)
{
    Token token;
    int start_pos = lexer->curr_pos;

    while(isalnum(peek_lexer(lexer)) || ispunct(peek_lexer(lexer)))
        advance_lexer(lexer);

    char* value = substr((char*)lexer->src, start_pos, lexer->curr_pos + 1);
    token.type = TOKEN_TEXT;
    token.value = value;

    return token;
}

Token get_next_token(Lexer* lexer)
{
    skip_whitespace(lexer);
    Token token;

    if(lexer->curr_char == '\n')
        token = create_token("\n", TOKEN_NEWLINE);

    else if(lexer->curr_char == '#')
        token = create_token("#", TOKEN_HASHTAG);

    else if(lexer->curr_char == '*')
        token = create_token("*", TOKEN_ASTERISK);

    else if(lexer->curr_char == '_')
        token = create_token("_", TOKEN_UNDERSCORE);

    else if(isalnum(lexer->curr_char) || ispunct(lexer->curr_char))
        token = create_text_token(lexer);

    else if(lexer->curr_char == '\0') 
        token = create_token(NULL, TOKEN_EOF);

    advance_lexer(lexer);
    return token;
}