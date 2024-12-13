#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int parse(FILE *file, instruction *instructions) {
    add_predefined_symbols();
    char line[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];
    char tmp_line[MAX_LINE_LENGTH];
    int line_num = 0;
    int instr_num = 0;
    instruction instr;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        line_num++;
        strip(line);

        if (!*line) {
            continue;
        }

        if (instr_num >= MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }

        if (is_label(line)) {
            extract_label(line, label);

            if (!isalpha(label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }

            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
            }

            symtable_insert(label, instr_num);
            continue;
        }

        if (is_Atype(line)) {
            if (!parse_A_instruction(line, &instr.a_instr)) {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.type = A_TYPE;

            if (instr.a_instr.is_addr) {
                printf("A: %d\n", instr.a_instr.address);
            } else {
                printf("A: %s\n", instr.a_instr.label);
            }
        } else if (is_Ctype(line)) {
            strcpy(tmp_line, line);
            parse_C_instruction(tmp_line, &instr.c_instr);

            if (instr.c_instr.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }

            if (instr.c_instr.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            }

            if (instr.c_instr.jump == JMP_INVALID) {
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
            }

            instr.type = C_TYPE;

            printf("C: d=%d, c=%d, j=%d\n", instr.c_instr.dest, instr.c_instr.comp, instr.c_instr.jump);
        }

        instructions[instr_num++] = instr;
    }

    return instr_num;
}




char *strip(char *s) {
    char s_new[MAX_LINE_LENGTH + 1];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break;
        } else if (!isspace(*s2)) {
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';

    strcpy(s, s_new);
    return s;
}

bool is_Atype(const char *line) {
    return line[0] == '@' ? true : false;
}

bool is_label(const char *line) {
    int len = strlen(line);

    if (line[0] == '(' && line[len - 1] == ')') {
        return true;
    } else {
        return false;
    }
}

bool is_Ctype(const char *line) {
    if (!is_Atype(line) && !is_label(line)) {
        return true;
    } else {
        return false;
    }
}

char *extract_label(const char *line, char *label) {
    int len = strlen(line);
    if (line[0] == '(' && line[len - 1] == ')') {
        strncpy(label, line + 1, len - 2);
        label[len - 2] = '\0'; 
    }
    return label;
}

void add_predefined_symbols() {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
        predefined_symbol symbol = predefined_symbols[i];
        symtable_insert(symbol.name, symbol.address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
    char *s = malloc(strlen(line));
    if (!s) {
        return false;
    }
    
    strcpy(s, line + 1);

    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (s == s_end) {
        instr->label = malloc(strlen(s) + 1);
        if (!instr->label) {
            free(s);
            return false;
        }
        strcpy(instr->label, s);
        instr->is_addr = false;
        free(s);
        return true;
    }

    if (*s_end != '\0') {
        free(s);
        return false;
    }

    instr->address = (hack_addr)result;
    instr->is_addr = true;
    free(s);
    return true;
}

void parse_C_instruction(const char *line, c_instruction *instr) {
    char *jump = NULL;
    char *dest = NULL;
    char *comp = NULL;

    char tmp_line[MAX_LINE_LENGTH];
    strcpy(tmp_line, line); // Make a mutable copy of the line

    char *temp = strtok(tmp_line, ";");
    jump = strtok(NULL, ";");

    dest = strtok(temp, "=");
    comp = strtok(NULL, "=");

    if (comp == NULL) {
        comp = dest;
        dest = NULL;
    }

    int a_val;
    instr->jump = str_to_jumpid(jump);
    instr->dest = str_to_destid(dest);
    instr->comp = str_to_compid(comp, &a_val);
    instr->a = a_val;
}




