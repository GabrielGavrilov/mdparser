#ifndef __PARSER_H__
#define __PARSER_H__

#include "mdparser.h"
#include "lexer.h"
#include "tokens.h"
#include "node.h"
#include "stringlib.h"

typedef struct
{
    Lexer* lexer;
    Token curr_token;
    Token peek_token;
} Parser;

Parser* init_parser(Lexer* lexer);
void free_parser(Parser* parser);
int check_parser(Parser* parser, TokenType type);
int check_peek_parser(Parser* parser, TokenType type);
void advance_parser(Parser* parser);
void parse_to_html(Parser* parser);

#endif