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
#define MAX_LINE_LENGTH  200

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }


    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    parse(file);
    
 
    fclose(file);

    return EXIT_SUCCESS;
}
