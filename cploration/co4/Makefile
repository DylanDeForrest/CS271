main: main.c 
CC = gcc
CFLAGS = -Wall -I.
LDFLAGS =
OBJFILES = main.o parser.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

Clean:
	rm -f $(OBJFILES) $(TARGET) *~
