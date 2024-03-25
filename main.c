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
		remember(buffer);	//file
		add_history(buffer);//runtime

		char* argv[MAX_ARGS]; //too big?
		int redirect = redirector(buffer);
		int argc = buffer2Args(buffer, argv);
		if(strcmp(argv[0],        "exit") == 0){
			printf("Goodbye!!\n");
			return 0;
		} else if(strcmp(argv[0], "cd") == 0) {
			chdir(argv[1]);
		}

		int childPid = fork();
		if(childPid == 0){
			if(redirect){
				dup2(redirect, 1);
			}
			if(strcmp(argv[0],        "echo") == 0){
				echo(argc, argv);
			} else if(strcmp(argv[0], "fortune") == 0) { 
				fortune(argc, argv);
			} else if(strcmp(argv[0], "history") == 0){
				history(argc, argv);
			} else if(strcmp(argv[0], "cp") == 0){
				cp(argc, argv);
			} else if(strcmp(argv[0], "free") == 0){
				free_mem();
			} else { //execute
				execvp(argv[0], argv);
			}
			exit(0);
		}
		waitpid(childPid, &retStatus, 0);
		free(buffer);
	}
	return 0;
};