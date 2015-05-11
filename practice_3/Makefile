pr3: main.o calc.o
	gcc -m32 main.o calc.o -o pr3
main.o: main.c
	gcc -c -m32 main.c
calc.o: calc.asm
	nasm -felf32 calc.asm
