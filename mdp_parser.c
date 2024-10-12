#include "mdp_parser.h"

Parser* init_parser(Lexer* lexer)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->flag = NONE;

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

Node* create_literal(char* value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->literal.type = LITERAL;
    node->literal.value = value;

    return node;
}

Node* create_unary(HtmlBlockType block, Node* child)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->type = UNARY;
    node->unary.type = UNARY;
    node->unary.block = block;
    node->unary.child = child;
    
    return node;
}

Node* create_binary(Node* left, Node* right)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->type = BINARY;
    node->binary.left = left;
    node->binary.right = right;

    return node;
}

Node* parse_unary(Parser* parser)
{
    Node* node = (Node*)malloc(sizeof(Node));

    if(check_parser(parser, TOKEN_TEXT))
    {
        node = create_unary(PARAGRAPH, create_literal( parse_text(parser, TOKEN_NEWLINE)));
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

        node = create_unary(heading, create_literal(parse_text(parser, TOKEN_NEWLINE)));
    }

    return node;
}

Node* parse_binary(Parser* parser)
{
    Node* node = parse_unary(parser);

    if(check_parser(parser, TOKEN_ASTERISK))
    {
        advance_parser(parser);
        if(parser->flag != UL)
        {
            parser->flag = UL;
            node = create_binary(
                create_unary(OPEN_UL, create_literal(NULL)),
                create_unary(LIST_ITEM, create_literal(parse_text(parser, TOKEN_NEWLINE)))
            );
        }
        else
        {
            char* list_item_text = parse_text(parser, TOKEN_NEWLINE);

            if(check_peek_parser(parser, TOKEN_ASTERISK))
            {
                node = create_unary(LIST_ITEM, create_literal(list_item_text));
            }
            else
            {
                parser->flag = NONE;
                node = create_binary(
                    create_unary(LIST_ITEM, create_literal(parse_text(parser, TOKEN_NEWLINE))),
                    create_unary(CLOSED_UL, create_literal(NULL))
                );
            }
        }
    }

    if(check_parser(parser, TOKEN_NEWLINE) && check_peek_parser(parser, TOKEN_NEWLINE))
    {
        node = create_unary(CLOSED_UL, create_literal(NULL));
    }

    parse_newline(parser);
    return node;
}

void parse_to_html(Parser* parser)
{
    while(parser->curr_token.type != TOKEN_EOF)
    {   
        Node* node = parse_binary(parser);
        node_to_html(node);
    }
}