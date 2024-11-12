// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.


// Mult.asm
// Multiplies R0 and R1 and stores the result in R2.

// Mult.asm
// Multiplies R0 and R1 and stores the result in R2.
// R0 contains the multiplier
// R1 contains the multiplicand
// R2 will store the result

// Mult.asm
// Multiplies R0 and R1 and stores the result in R2.

// Mult.asm
// Multiplies R0 and R1 and stores the result in R2.
// Assumes R0 and R1 contain non-negative values.
// Mult.asm
// Multiplies R0 and R1 and stores the result in R2.
// Uses R0 as the multiplier and R1 as the multiplicand.

@2
M=0          // Initialize R2 to 0

@0
D=M          // Load R0 multiplier into D
@END
D;JLE        // If R0 <= 0 jump to END

(LOOP)
@1
D=M          // Load R1 multiplicand into D
@2
M=D+M        // R2 = R2 + R1

@0
M=M-1        // Decrement R0 by 1
D=M          // Load the updated value of R0 into D
@LOOP
D;JGT        // If R0 > 0 repeat the loop

(END)
@END
0;JMP        // Infinite loop to end the program

