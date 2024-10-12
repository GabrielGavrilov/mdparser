#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

typedef union Node Node;

typedef enum
{
    HEADING_1 = 1,
    HEADING_2,
    HEADING_3,
    HEADING_4,

    ITALIC,
    BOLD,

    PARAGRAPH

} HtmlBlockType;

typedef enum 
{
    LITERAL,
    UNARY
} NodeType;

typedef struct
{
    NodeType type;
    char* value;
} LiteralNode;

typedef struct
{
    HtmlBlockType block;
    NodeType type;
    Node* child;
} UnaryNode;

union Node
{
    NodeType type;
    LiteralNode literal;
    UnaryNode unary;
};

#endif