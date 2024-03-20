#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "utils.h"

int main() {
	printf(WELCOME_MSG);
	char buffer[BUFF_LEN]; 
	while(1){
		pprompt();
		fgets(buffer, BUFF_LEN , stdin);
		if(strlen(buffer) == 1){
			continue;
		}
		struct Arguments args = buffer2Vector(buffer);
		//shell builtins
		if(strcmp(args.argv[0], "echo") == 0){
			echo(args);
		}
		if(strcmp(args.argv[0], "exit") == 0){
			break;
		}
	}
	return 0;
}