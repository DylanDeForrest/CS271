#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

void parse(FILE *file) {
    char line[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        strip(line);

        if (!*line) {
            continue;
        }

        if (is_Atype(line)) {
            printf("A  %s\n", line);
        } else if (is_label(line)) {
            extract_label(line, label);
            strcpy(line, label);
            printf("L  %s\n", line);
        } else if (is_Ctype(line)) {
            printf("C  %s\n", line);
        } else {
            printf("Unknown instruction type: %s\n", line);
        }
    }
}



char *strip(char *s) {
    char s_new[MAX_LINE_LENGTH + 1];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break;
        }
        else if (!isspace(*s2)) {
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

