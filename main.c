#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char SPACE[4] = " ";

int main() {
	printf("WELCOME!\n");
	while (1) {	
		printf("> ");
		char buffer[1024]; 
		fgets(buffer, 1024, stdin);
		char* token = strtok(strtok(buffer, "\n"), SPACE);
	
		if(strcmp(token, "exit") == 0) {
			return 0;
		}
		else if (strcmp(token, "echo") == 0) {
			token = strtok(NULL, SPACE);
			while(token != NULL){
				printf("%s ",token);
				token = strtok(NULL, SPACE);
			}
			printf("\n");
		}
	}
}