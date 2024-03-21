#include "utils.h"
#include "defines.h"
#include <stdlib.h>
#include <string.h>

void pprompt(){
	/*char path[128];
	getcwd(path, sizeof(path));
	char machinenamef[64];
	gethostname(machinenamef, 64);
	char newpath[128];

	int slashcount = 0;
	for (int i = 0; i < strlen(path); i++){
		if (path[i] == '/') {
			slashcount++;
		}
		//slashcount += (path[i] == '/')

		if (slashcount == 4) {
			// printf("%c\n", path[i]);
			// strcat(newpath, path[i]);
			newpath[i + slashcount] = path[i];
			newpath[i+ slashcount + 1] = '\0';
			//printf("%s", newpath);
		}
	}
	//printf("%i\n", slashcount);
	//printf("%s", newpath);
	printf("\n%s@%s:%s> ", getlogin(),  machinenamef , newpath);*/
	printf("\n%s@shitbox>", getlogin());
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