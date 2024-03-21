#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "defines.h"
#include "utils.h"

int main() {
	printf(WELCOME_MSG);
	char buffer[BUFF_LEN];
	memset(buffer, 0x0, BUFF_LEN);
	while(1){
		pprompt();
		fgets(buffer, BUFF_LEN, stdin);
		if(strlen(buffer) == 1){
			continue;
		}
		//maybe don't put this on the stack?
		char* argv[MAX_ARGS]; //too big?
		int argc = buffer2Args(buffer, argv);
		//shell builtins
		if(strcmp(argv[0], "echo") == 0){
			echo(argc, argv);
		} else if(strcmp(argv[0], "exit") == 0){
			break;
		}
		else if (strcmp(argv[0], "cd") == 0) {
			chdir(argv[1]);
			printf("%s", getcwd(NULL,100)); 
		} else {
			printf("Command not found: %s", argv[0]);
		//	execvpe(args.argv[0], args.argv);
		}

	}
	return 0;
}