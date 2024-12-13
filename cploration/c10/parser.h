#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH 198 
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type {
    INVALID = -1,
    A_TYPE,
    C_TYPE
};

typedef struct c_instruction {
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;
} c_instruction;


typedef struct {
    union {
        hack_addr address;
        char *label;
    };
    bool is_addr;
} a_instruction;

typedef struct {
    union {
        a_instruction a_instr;
        c_instruction c_instr;
    };
    enum instr_type type;
} instruction;

char *strip(char *s);
bool is_Atype(const char *);
bool is_Ctype(const char *);
bool is_label(const char *);
int parse(FILE *file, instruction *instructions);
void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(const char *line, c_instruction *instr);


char *extract_label(const char *line, char *label);

#endif // __PARSER_H__

