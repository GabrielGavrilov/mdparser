CC = gcc
FILES = mdparser.c lexer.c parser.c stringlib.c
CFLAGS = -w
TARGET = mdparser

mdparser:
	$(CC) $(FILES) -o $(TARGET) $(CFLAGS)

clean:
	rm -rf $(TARGET)