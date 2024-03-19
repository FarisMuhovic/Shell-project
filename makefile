CFLAGS=-Wall

run: compile
	build/MFshell

compile: main.o utils.o
	gcc -o build/MFshell build/main.o build/utils.o

main.o:
	mkdir -p build
	gcc -c -o build/main.o main.c

utils.o:
	mkdir -p build
	gcc -c -o build/utils.o utils.c 

clean:
	rm -rf build