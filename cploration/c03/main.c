/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Dylan De Forrest
 * [TERM] FALL 2024
 * 
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH  200
 
int main(int argc, const char *argv[])
{
  //Exercise 2
  if (argc != 2) {
    printf("Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //Exercise 3
  FILE *fin = fopen(argv[1], "r");
  if (fin == NULL) {
    perror("Unable to open file!");
    exit(EXIT_FAILURE);
}

  //Exercise 4
  char out_file[256];
  snprintf(out_file, sizeof(out_file), "%s.echo", argv[1]);

  FILE *fout = fopen(out_file, "w+");
    if (fout == NULL) {
        perror("Unable to create output file!");
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    //Exercise 5
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;

    while (fgets(line, sizeof(line), fin)) {
        line_num++;
        printf("[%04d] %s", line_num, line);
        fprintf(fout, "%s", line);
    }

    fclose(fin);
    fclose(fout);

    return 1;
}
