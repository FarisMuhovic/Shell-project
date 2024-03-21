#include "utils.h"
#include "defines.h"
#include <stdlib.h>
#include <string.h>

void pprompt(int retStatus){
	char path[128];
	getcwd(path,128);
	char machinenamef[64];
	gethostname(machinenamef, 64);
	strcat(path, "~$");
	printf("\n%s@%s:%s ", getlogin(),  machinenamef , path);
}

int buffer2Args(char *buffer, char** argv){
	int argc = 0;
	int navodnik = 0; //`'"
	int len = strlen(buffer);
	argv[0] = strtok(buffer, "\n");
	for(int i=0; i<len; i++){
		//exit if max args reached??
		if(buffer[i] == ' ' && navodnik == 0){
			argc++;
			buffer[i] = '\0';
			argv[argc] = buffer+i+1;
		} else if (buffer[i] == '\"'){
			navodnik ^= 0b001;	
		} else if (buffer[i] == '\''){
			navodnik ^= 0b010;
		} else if (buffer[i] == '`'){
			navodnik ^= 0b100;
		}
	}
	return argc;
}

int echo(int argc, char** argv){
	for(int i=1; i<=argc; i++){
		printf("%s ",argv[i]);
	}
	return 0;
}