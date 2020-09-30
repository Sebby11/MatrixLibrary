#CruzID: Seamedin                      Course: CSE 101
#Date: October 26, 2019                FileName: Makefile
#Description: Makefile for the Sparce client

Sparce: Sparce.o Matrix.o List.o
	gcc -o Sparce Sparce.o Matrix.o List.o

Sparce.o : Sparce.c Matrix.h
	gcc -c -std=c99 -Wall Sparce.c

Matrix.o : Matrix.c Matrix.h
	gcc -c -std=c99 -Wall Matrix.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Sparce Sparce.o Matrix.o List.o
