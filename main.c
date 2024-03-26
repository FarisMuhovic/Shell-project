#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defines.h"
#include "main.h"
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
		//printArgs(argc,argv);
		waitpid(run(argc, argv, redirect), &retStatus, 0);
		free(buffer);
	}
	return 0;
}

int run(int argc, char** argv, int redirect){
	int childPid = fork();
	if(childPid == 0){
		int pindex = handlePipe(argv);
		int cijev[2];
		if(pindex != 0){
			if(pipe(cijev)){
				perror("Could not create pipe");
				return -1;
			}
			if(fork() == 0){
				close(cijev[1]);
				dup2(cijev[0], STDIN_FILENO);
				run(argc-pindex-1, argv+pindex+1, redirect);
				exit(0);
			}
			close(cijev[0]);
			dup2(cijev[1], STDOUT_FILENO);
			argc = pindex-1;
			redirect = -1; //no way there will be a redirect
		}
		//fprintf(stderr, "I am %s:%d\n", argv[0], getpid());
		//printArgs(argc, argv);
		if(redirect != -1){
			dup2(redirect, STDOUT_FILENO);
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
			printf("Command not found: %s\n", argv[0]);
		}
		exit(0);
	}
	return childPid;
}