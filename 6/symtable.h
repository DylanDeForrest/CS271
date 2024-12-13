#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdint.h> // For int16_t

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct {
    char *name;
    hack_addr addr;
} Symbol;

void symtable_insert(const char *key, hack_addr addr);
Symbol *symtable_find(char *key);
void symtable_print_labels();
void symtable_display_table();

#endif // __SYMTABLE_H__
