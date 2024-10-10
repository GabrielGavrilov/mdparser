#include "parser.h"

Parser* init_parser(Lexer* lexer)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;

    advance_parser(parser);
    advance_parser(parser);

    return parser;
}

void free_parser(Parser* parser)
{
    free(parser);
    free_lexer(parser->lexer);
    parser = NULL;
}

int check_parser(Parser* parser, TokenType type)
{
    return type == parser->curr_token.type;
}

int check_peek_parser(Parser* parser, TokenType type)
{
    return type == parser->peek_token.type;
}

void advance_parser(Parser* parser)
{
    parser->curr_token = parser->peek_token;
    parser->peek_token = get_next_token(parser->lexer);
}

void parse_newline(Parser* parser)
{
    while(parser->curr_token.type == TOKEN_NEWLINE)
    {
        advance_parser(parser);
    }
}

char* parse_text(Parser* parser)
{
    char* temp = "";

    while(parser->peek_token.type != TOKEN_NEWLINE)
    {
        cat(&parser->curr_token.value, " ");
        cat(&temp, parser->curr_token.value);
        advance_parser(parser);
    }

    cat(&temp, parser->curr_token.value);
    advance_parser(parser);

    return temp;
}

Node* parse_literal(Parser* parser)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->literal.type = LITERAL;
    node->literal.value = parse_text(parser);

    return node;
}

Node* create_unary(Parser* parser, HtmlBlockType block, Node* child)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->unary.type = UNARY;
    node->unary.block = block;
    node->unary.child = child;
    return node;
}

Node* parse_unary(Parser* parser)
{
    Node* node = (Node*)malloc(sizeof(Node));

    if(check_parser(parser, TOKEN_TEXT))
    {
        node = create_unary(parser, PARAGRAPH, parse_literal(parser));
    }

    if(check_parser(parser, TOKEN_HASHTAG))
    {
        advance_parser(parser);
        node = create_unary(parser, HEADING, parse_literal(parser));
    }

    parse_newline(parser);
    return node;
}


void parse_to_html(Parser* parser)
{

    while(parser->curr_token.type != TOKEN_EOF)
    {   
        Node* node = parse_unary(parser);
        printf("(%d, %d, (%d, %s)\n",
            node->unary.type, 
            node->unary.block, 
            node->unary.child->literal.type,
            node->unary.child->literal.value);
    }
}