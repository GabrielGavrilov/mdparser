#ifndef __MDP_PARSER_H__
#define __MDP_PARSER_H__

#include "mdparser.h"
#include "mdp_lexer.h"
#include "mdp_tokens.h"
#include "mdp_node.h"
#include "mdp_common.h"
#include "mdp_translater.h"

typedef enum
{
    NONE,
    UL
} ParserFlag;

typedef struct
{
    Lexer* lexer;
    Token curr_token;
    Token peek_token;
    ParserFlag flag;
} Parser;

Parser* init_parser(Lexer* lexer);
void free_parser(Parser* parser);
int check_parser(Parser* parser, TokenType type);
int check_peek_parser(Parser* parser, TokenType type);
void advance_parser(Parser* parser);
void parse_to_html(Parser* parser);

#endif