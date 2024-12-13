#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY NULL

static Symbol *hashArray[SYMBOL_TABLE_SIZE];

static int hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % SYMBOL_TABLE_SIZE;
}

void symtable_insert(const char *key, hack_addr addr) {
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(key);
    symbol->addr = addr;

    int index = hash((char *)key);

    while (hashArray[index] != EMPTY && strcmp(hashArray[index]->name, key) != 0) {
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }

    hashArray[index] = symbol;
}


Symbol *symtable_find(char *key) {
    int index = hash(key);

    while (hashArray[index] != EMPTY) {
        if (strcmp(hashArray[index]->name, key) == 0) {
            return hashArray[index];
        }
        index = (index + 1) % SYMBOL_TABLE_SIZE;
    }

    return NULL;
}

void symtable_print_labels() {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != EMPTY) {
            printf("{%s,%d}\n", hashArray[i]->name, hashArray[i]->addr);
        }
    }
}

void symtable_display_table() {
    printf("Symbol Table:\n");
    symtable_print_labels();
}
