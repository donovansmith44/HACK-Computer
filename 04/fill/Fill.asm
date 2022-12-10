// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(LOOP) //listen to keyboard

@8192
D=A

@n //n=8192
M=D

@KBD
D=M

@BLACKEN //go to fill screen if m[kbd]=0. Else clear
D;JGT

@CLEAR
D;JEQ

(BLACKEN)
@SCREEN
M=-1
A=A+D //A=25376+8192
M=-1 //blacken pixels associated with word A

@n //decrement addresses while n =/= 0
M=M-1
D=M

@BLACKEN
D;JNE

@LOOP
D;JEQ

(CLEAR)
@SCREEN
M=0
A=A+D //A=25376
M=0 //clear pixels associated with word A

@n //decrement addresses while n =/= 0
M=M-1
D=M

@CLEAR
D;JNE

@LOOP
D;JEQ