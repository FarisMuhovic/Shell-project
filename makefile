run: compile
	build/MFshell

compile:
	mkdir -p build
	gcc -Wall main.c -o build/MFshell

clean:
	rm -rf build