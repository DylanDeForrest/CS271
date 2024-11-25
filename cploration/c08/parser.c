#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void parse(FILE *file) {
    char line[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];
    int line_num;
    int instr_num;

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

        if (is_Atype(line) || is_Ctype(line)) {
            printf("%u: %c  %s\n", instr_num, is_Atype(line) ? 'A' : 'C', line);
        }
        instr_num++;
    }
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
