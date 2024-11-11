

#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

typedef int16_t hack_addr;
typedef int16_t opcode;

char *strip(char *s);
void parse(FILE * file);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);