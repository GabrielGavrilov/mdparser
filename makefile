CC = gcc
FILES = mdparser.c mdp_lexer.c mdp_parser.c mdp_translater.c mdp_common.c
CFLAGS = -w
TARGET = mdparser

mdparser:
	$(CC) $(FILES) -o $(TARGET) $(CFLAGS)

clean:
	rm -rf $(TARGET)