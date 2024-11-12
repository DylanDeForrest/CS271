// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.

// Fill.asm
// Fills or clears the screen based on keyboard input.
// The screen address range is 16384-24575 (8K), and the keyboard address is 24576.

@24575
D=A
@0
M=D           // Store the maximum screen address in R0

@SCREEN
D=A
@1
M=D           // Store the starting screen address in R1 

(LOOP)
@KBD
D=M           // D = keyboard value
@FILL
D;JGT         // If a key is pressed D > 0 jump to FILL
@CLEAR
0;JMP         // If no key is pressed D == 0 jump to CLEAR

(FILL)
@0
D=M
@1
D=D-M
@LOOP
D;JLT         // If R1 exceeds max screen address go back to LOOP

@1
D=M
A=D
M=-1          // Set this screen address to black

@1
M=D+1         // Increment current address in R1 by 1
@FILL
0;JMP         // Repeat filling process

(CLEAR)
@SCREEN
D=A
@1
D=D-M
@LOOP
D;JGT         // If current address is less than start go back to LOOP

@1
D=M
A=D
M=0           // Clear this screen address set to 0

@1
M=D-1         // Decrement current address in R1 by 1
@CLEAR
0;JMP         // Repeat clearing process
