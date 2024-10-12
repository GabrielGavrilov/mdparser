#include "mdp_translater.h"

void translate_to_header(Node* node, char** buffer)
{
	int heading_block = node->unary.block;
	char* value = node->unary.child->literal.value;
	int heading_size = strlen(value) + 7 + 2;
	char* heading = (char*)malloc(heading_size + 1);
	char s_level[2];

	int level = (heading_block == 1) ? 1 : 
				(heading_block == 2) ? 2 :
				(heading_block == 3) ? 3 : 4;

	sprintf(s_level, "%d", level);
	snprintf(heading, heading_size + 1, "<h%s>%s</h%s>", s_level, value, s_level);

	cat(buffer, heading);
}

void translate_to_paragraph(Node* node, char** buffer)
{
	char* value = node->unary.child->literal.value;
	int paragraph_size = strlen(value) + 7;
	char* paragraph = (char*)malloc(paragraph_size + 1);

	snprintf(paragraph, paragraph_size + 1, "<p>%s</p>", value);

	cat(buffer, paragraph);
}

void node_to_html_block(Node* node)
{
	char* buffer = (char*)malloc(4096);

	switch(node->unary.block)
	{
		case HEADING_1:
		case HEADING_2:
		case HEADING_3:
		case HEADING_4:
			translate_to_header(node, &buffer);
			break;
		case PARAGRAPH:
			translate_to_paragraph(node, &buffer);
			break;
	}

	printf("%s\n", buffer);
}