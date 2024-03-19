#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "utils.h"

int main() {
	printf(WELCOME_MSG);
	char buffer[1024]; 
	while(1){	
		pprompt();
		fgets(buffer, 1024, stdin);
		
		char* token = strtok(strtok(buffer, "\n"), " ");

		if(strcmp(token, "exit") == 0) {
			return 0;
		}
		else if (strcmp(token, "echo") == 0) {
			token = strtok(NULL, " ");
			while(token != NULL){
				printf("%s ",token);
				token = strtok(NULL, " ");
			}
			printf("\n");
		}
	}
}