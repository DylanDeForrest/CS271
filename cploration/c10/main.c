/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Dylan De Forrest
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "symtable.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
    if (instructions == NULL) {
        fclose(file);
        exit_program(EXIT_CANNOT_OPEN_FILE, "Memory allocation failed");
    }

    int num_instructions = parse(file, instructions);

    //printf("Parsed %d instructions.\n", num_instructions);

    free(instructions);
    fclose(file);

    return EXIT_SUCCESS;
}
