#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct Arguments{
	int argc;
	char** argv;
};

static inline void pprompt(){
	char path[128];
	getcwd(path, sizeof(path));
	char machinenamef[64];
	gethostname(machinenamef, 64);
	char newpath[128];

	printf("%ld\n", strlen(path));

	int slashcount = 0;
	for (int i = 0; i < strlen(path); i++)
	{

		if (path[i] == 47) {
			slashcount++;
		}

		if (slashcount == 4) {
			// printf("%c\n", path[i]);
			// strcat(newpath, path[i]);
			newpath[i + slashcount] = path[i];
			newpath[i+ slashcount + 1] = '\0';
			printf("%s", newpath);
		}
	}
	printf("%i\n", slashcount);
	printf("%s", newpath);
	printf("%s@%s:%s> ", getlogin(),  machinenamef , newpath);
}

int echo(struct Arguments);

struct Arguments buffer2Vector(char*);