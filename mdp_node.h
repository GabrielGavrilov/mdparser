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

    PARAGRAPH,

    OPEN_UL,
    CLOSED_UL,
    LIST_ITEM

} HtmlBlockType;

typedef enum 
{
    LITERAL,
    UNARY,
    BINARY
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

typedef struct 
{
    NodeType type;
    Node* left;
    Node* right;
} BinaryNode;

union Node
{
    NodeType type;
    LiteralNode literal;
    UnaryNode unary;
    BinaryNode binary;
};

#endif