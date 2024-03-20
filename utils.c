#include "utils.h"
#include "defines.h"
#include <stdlib.h>
#include <string.h>

void pprompt(){
	char path[128];
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
	printf("%s@%s:%s> ", getlogin(),  machinenamef , newpath);
}

struct Arguments buffer2Vector(char *buffer){
	int navodnik = 0; //`'"
	int argc = 1;
	int len = strlen(buffer);
	char** argv[MAX_ARGS]; //too big?
	argv[0] = buffer;
	for(int i=0; i<len; i++){
		//exit if max args reached??
		if(buffer[i] == ' ' && navodnik == 0){
			buffer[i] = '\0';
			argv[argc] = buffer+i+1;
			argc++;
		} else if (buffer[i] == '\"'){
			navodnik ^= 0b001;	
		} else if (buffer[i] == '\''){
			navodnik ^= 0b010;
		} else if (buffer[i] == '`'){
			navodnik ^= 0b100;
		}
	}
	struct Arguments args = {argc, argv};
	return args;
}

int echo(struct Arguments in){
	for(int i=0; i<in.argc; i++){
		printf("%s ",in.argv[i]);
	}
	return 0;
}