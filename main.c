#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defines.h"
#include "utils.h"
#include "fortune.h"
#include "history.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

int main() {
	welcomeText();
	char* buffer;
	int retStatus = 0;
	while((buffer = readline(prompt(retStatus))) != NULL) {
		if(strlen(buffer) == 0){
			continue;
		}
		remember(buffer);	//system
		add_history(buffer);//runtime
		
		//maybe don't put this on the stack?
		char* argv[MAX_ARGS]; //too big?
		int argc = buffer2Args(buffer, argv);
		//shell builtins
		if(strcmp(argv[0], "echo") == 0){
			echo(argc, argv);
		} else if(strcmp(argv[0], "exit") == 0){
			printf("Goodbye!!\n");
			return 0;
		} else if (strcmp(argv[0], "cd") == 0) {
			chdir(argv[1]);
		} else if (strcmp(argv[0], "fortune") == 0) { 
			fortune();
		} else if (strcmp(argv[0], "history") == 0){
			recall();
		} else if(strcmp(argv[0], "cp") == 0){
			cp(argc, argv);
		} else if(strcmp(argv[0], "free") == 0){
			free_mem();
		}
		else {
			int childPid = fork();
			if(childPid == 0){
				execvp(argv[0], argv);
			}
    		waitpid(childPid, &retStatus, 0);
		}
		free(buffer);
	}
	return 0;
}