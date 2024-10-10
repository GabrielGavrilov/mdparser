#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

typedef union Node Node;

typedef enum
{
    HEADING = 100,
    PARAGRAPH = 101
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