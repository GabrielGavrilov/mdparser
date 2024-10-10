#include "mdparser.h"

#include "parser.h"

int main(int argc, char** argv)
{

    const char* src = "# this is a heading\nthis is a paragraph";

    Lexer* lexer = init_lexer(src);
    Parser* parser = init_parser(lexer);

    parse_to_html(parser);

    return 0;
}