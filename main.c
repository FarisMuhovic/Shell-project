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
		fgets(buffer, BUFF_LEN , stdin);
		if(strlen(buffer) == 1){
			continue;
		}
		struct Arguments args = buffer2Vector(buffer);
		//shell builtins
		printf("Checking %s...\n", args.argv[0]);
		if(strcmp(args.argv[0], "echo") == 0){
			echo(args);
		} else if(strcmp(args.argv[0], "exit") == 0){
			break;
		} else {
			printf("running %s...\n", args.argv[0]);
		//	execvpe(args.argv[0], args.argv);
		}

	}
	return 0;
}