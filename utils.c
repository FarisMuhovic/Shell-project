#include "utils.h"
#include "defines.h"
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>


char* prompt(int retStatus){
	static char prompt[BUFF_LEN];
	char path[128];
	getcwd(path,128);
	char machinenamef[64];
	gethostname(machinenamef, 64);
	char concatedpath[150];
	sprintf(concatedpath, "/home/%s", getlogin());
	if (strncmp(path, concatedpath, strlen(concatedpath)) == 0) {
		sprintf(concatedpath, "~%s", path + strlen(concatedpath));
	} else  {
		strcpy(concatedpath, path);
	}

	sprintf(prompt, GREEN"\n%s"WHITE"@"GREEN"%s:"BLUE"%s"WHITE"$"RESET, getlogin(),  machinenamef , concatedpath);
	return prompt;
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

const char logo[] = {

};

void welcomeText() {
	struct utsname system_info;

	if (uname(&system_info) == -1) {
		perror("uname");
	}
	printf("\n");
	printf(GREEN"%s\n\n", "Welcome!"RESET);
	printf(WHITE"%s\n", "System information "RESET);
	printf("%s%s%s\n", system_info.sysname, "-", system_info.release);
	printf("%s%s%s\n"RESET, system_info.nodename, "-" ,system_info.machine );	

}