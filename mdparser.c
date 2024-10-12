#include "mdparser.h"
#include "mdp_parser.h"

int main(int argc, char** argv)
{

    MDPFile* source = open_file(argv[1]);

    Lexer* lexer = init_lexer(source->buffer);
    Parser* parser = init_parser(lexer);

    parse_to_html(parser);

    return 0;
}