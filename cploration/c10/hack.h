#ifndef __HACK_H__
#define __HACK_H__

#include <stdint.h>
#include <string.h>

#define MAX_NAME_LENGTH 6
#define NUM_PREDEFINED_SYMBOLS 23

typedef enum {
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JMP_JGT = 1,
    JMP_JEQ = 2,
    JMP_JGE = 3,
    JMP_JLT = 4,
    JMP_JNE = 5,
    JMP_JLE = 6,
    JMP_JMP = 7
} jump_id;

typedef enum {
    DEST_INVALID = -1,
    DEST_NULL = 0,
    DEST_M = 1,
    DEST_D = 2,
    DEST_MD = 3,
    DEST_A = 4,
    DEST_AM = 5,
    DEST_AD = 6,
    DEST_AMD = 7
} dest_id;

typedef enum {
    COMP_INVALID = -1,
    COMP_0 = 42,
    COMP_1 = 63,
    COMP_NEGATIVE_1 = 58,
    COMP_D = 12,
    COMP_A = 48,
    COMP_NOT_D = 13,
    COMP_NOT_A = 49,
    COMP_NEGATIVE_D = 15,
    COMP_NEGATIVE_A = 51,
    COMP_D_PLUS_1 = 31,
    COMP_A_PLUS_1 = 55,
    COMP_D_MINUS_1 = 14,
    COMP_A_MINUS_1 = 50,
    COMP_D_PLUS_A = 2,
    COMP_D_MINUS_A = 19,
    COMP_A_MINUS_D = 7,
    COMP_D_AND_A = 0,
    COMP_D_OR_A = 21,
    COMP_M = 48,
    COMP_NOT_M = 49,
    COMP_NEGATIVE_M = 51,
    COMP_M_PLUS_1 = 55,
    COMP_M_MINUS_1 = 50,
    COMP_D_PLUS_M = 2,
    COMP_D_MINUS_M = 19,
    COMP_M_MINUS_D = 7,
    COMP_D_AND_M = 0,
    COMP_D_OR_M = 21
} comp_id;

typedef enum {
    SYM_R0 = 0,
    SYM_R1 = 1,
    SYM_R2 = 2,
    SYM_R3 = 3,
    SYM_R4 = 4,
    SYM_R5 = 5,
    SYM_R6 = 6,
    SYM_R7 = 7,
    SYM_R8 = 8,
    SYM_R9 = 9,
    SYM_R10 = 10,
    SYM_R11 = 11,
    SYM_R12 = 12,
    SYM_R13 = 13,
    SYM_R14 = 14,
    SYM_R15 = 15,
    SYM_SP = 0,
    SYM_LCL = 1,
    SYM_ARG = 2,
    SYM_THIS = 3,
    SYM_THAT = 4,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576
} symbol_id;

typedef struct {
    const char *name;
    int16_t address;
} predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", SYM_R0},    {"R1", SYM_R1},    {"R2", SYM_R2},
    {"R3", SYM_R3},    {"R4", SYM_R4},    {"R5", SYM_R5},
    {"R6", SYM_R6},    {"R7", SYM_R7},    {"R8", SYM_R8},
    {"R9", SYM_R9},    {"R10", SYM_R10},  {"R11", SYM_R11},
    {"R12", SYM_R12},  {"R13", SYM_R13},  {"R14", SYM_R14},
    {"R15", SYM_R15},  {"SP", SYM_SP},    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},  {"THIS", SYM_THIS},{"THAT", SYM_THAT},
    {"SCREEN", SYM_SCREEN}, {"KBD", SYM_KBD}
};

static inline jump_id str_to_jumpid(const char *s) {
    if (s == NULL) return JMP_NULL;
    if (strcmp(s, "JGT") == 0) return JMP_JGT;
    if (strcmp(s, "JEQ") == 0) return JMP_JEQ;
    if (strcmp(s, "JGE") == 0) return JMP_JGE;
    if (strcmp(s, "JLT") == 0) return JMP_JLT;
    if (strcmp(s, "JNE") == 0) return JMP_JNE;
    if (strcmp(s, "JLE") == 0) return JMP_JLE;
    if (strcmp(s, "JMP") == 0) return JMP_JMP;
    return JMP_INVALID;
}

static inline dest_id str_to_destid(const char *s) {
    if (s == NULL || strcmp(s, "") == 0) return DEST_NULL;
    if (strcmp(s, "M") == 0) return DEST_M;
    if (strcmp(s, "D") == 0) return DEST_D;
    if (strcmp(s, "MD") == 0) return DEST_MD;
    if (strcmp(s, "A") == 0) return DEST_A;
    if (strcmp(s, "AM") == 0) return DEST_AM;
    if (strcmp(s, "AD") == 0) return DEST_AD;
    if (strcmp(s, "AMD") == 0) return DEST_AMD;
    return DEST_INVALID;
}

static inline comp_id str_to_compid(const char *s, int *a) {
    *a = 0;
    if (s == NULL) return COMP_INVALID;

    // Handle a = 0 computations
    if (strcmp(s, "0") == 0) return COMP_0;
    if (strcmp(s, "1") == 0) return COMP_1;
    if (strcmp(s, "-1") == 0) return COMP_NEGATIVE_1;
    if (strcmp(s, "D") == 0) return COMP_D;
    if (strcmp(s, "A") == 0) return COMP_A;
    if (strcmp(s, "!D") == 0) return COMP_NOT_D;
    if (strcmp(s, "!A") == 0) return COMP_NOT_A;
    if (strcmp(s, "-D") == 0) return COMP_NEGATIVE_D;
    if (strcmp(s, "-A") == 0) return COMP_NEGATIVE_A;
    if (strcmp(s, "D+1") == 0) return COMP_D_PLUS_1;
    if (strcmp(s, "A+1") == 0) return COMP_A_PLUS_1;
    if (strcmp(s, "D-1") == 0) return COMP_D_MINUS_1;
    if (strcmp(s, "A-1") == 0) return COMP_A_MINUS_1;
    if (strcmp(s, "D+A") == 0) return COMP_D_PLUS_A;
    if (strcmp(s, "D-A") == 0) return COMP_D_MINUS_A;
    if (strcmp(s, "A-D") == 0) return COMP_A_MINUS_D;
    if (strcmp(s, "D&A") == 0) return COMP_D_AND_A;
    if (strcmp(s, "D|A") == 0) return COMP_D_OR_A;

    // Handle a = 1 computations
    *a = 1;
    if (strcmp(s, "M") == 0) return COMP_M;
    if (strcmp(s, "!M") == 0) return COMP_NOT_M;
    if (strcmp(s, "-M") == 0) return COMP_NEGATIVE_M;
    if (strcmp(s, "M+1") == 0) return COMP_M_PLUS_1;
    if (strcmp(s, "M-1") == 0) return COMP_M_MINUS_1;
    if (strcmp(s, "D+M") == 0) return COMP_D_PLUS_M;
    if (strcmp(s, "D-M") == 0) return COMP_D_MINUS_M;
    if (strcmp(s, "M-D") == 0) return COMP_M_MINUS_D;
    if (strcmp(s, "D&M") == 0) return COMP_D_AND_M;
    if (strcmp(s, "D|M") == 0) return COMP_D_OR_M;

    return COMP_INVALID;
}

#endif // __HACK_H__

