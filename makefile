CFLAGS=-Wall -g3


run: build/MFshell
	build/MFshell

build build/MFshell: build/main.o build/utils.o build/history.o
	gcc ${CFLAGS} build/*.o -o build/MFshell

build/%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*