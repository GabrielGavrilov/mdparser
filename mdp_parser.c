#include "mdp_parser.h"

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

char* parse_text(Parser* parser, TokenType* stop_token)
{
    char* temp = "";

    while(parser->peek_token.type != stop_token)
    {
        cat(&parser->curr_token.value, " ");
        cat(&temp, parser->curr_token.value);
        advance_parser(parser);
    }

    cat(&temp, parser->curr_token.value);
    advance_parser(parser);

    return temp;
}

Node* create_literal(Parser* parser, char* value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->literal.type = LITERAL;
    node->literal.value = value;

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
        node = create_unary(parser, PARAGRAPH, create_literal(parser, parse_text(parser, TOKEN_NEWLINE)));
    }

    if(check_parser(parser, TOKEN_HASHTAG))
    {
        advance_parser(parser);
        int level = 1;

        while(check_parser(parser, TOKEN_HASHTAG) && level < 4)
        {
            advance_parser(parser);
            level++;
        }

        HtmlBlockType heading = (level == 1) ? HEADING_1 :
                                (level == 2) ? HEADING_2 :
                                (level == 3) ? HEADING_3 : HEADING_4;

        node = create_unary(parser, heading, create_literal(parser, parse_text(parser, TOKEN_NEWLINE)));
    }

    if(check_parser(parser, TOKEN_ASTERISK))
    {
        advance_parser(parser);
        int level = 1;

        while(check_parser(parser, TOKEN_ASTERISK) && level < 2)
        {
            advance_parser(parser);
            level++;
        }


        HtmlBlockType block = (level == 1) ? ITALIC : BOLD;
        node = create_unary(parser, block, create_literal(parser, parse_text(parser, TOKEN_ASTERISK)));

        switch(level)
        {
            case 2:
                advance_parser(parser);
            default:
                advance_parser(parser);
                break;
        }
    }

    parse_newline(parser);
    return node;
}


void parse_to_html(Parser* parser)
{

    while(parser->curr_token.type != TOKEN_EOF)
    {   
        Node* node = parse_unary(parser);
        node_to_html_block(node);
    }
}