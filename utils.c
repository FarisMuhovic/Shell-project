#include "utils.h"
#include "defines.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
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

	sprintf(prompt, GREEN"\n%s"WHITE"@"GREEN"%s:"BLUE"%s"WHITE"$ "RESET, getlogin(),  machinenamef , concatedpath);
	return prompt;
}

int buffer2Args(char *buffer, char** argv){
	int argc = 0;
	int navodnik = 0;//bool
	int len = strlen(buffer);
	argv[0] = strtok(buffer, "\n");
	for(int i=0; i<len; i++){
		//exit if max args reached??
		if(buffer[i] == ' ' && !navodnik){
			buffer[i] = '\0';
			argv[++argc] = buffer+i+1;
			//	proper thing to do would be:
			//strcpy(buffer+i,buffer+i+1);
			//argv[++argc] = buffer+i;
			//	but it would trade a little bit of memory for a lot of copying...
		} else if (buffer[i] == '\"'){
			navodnik = !navodnik;
			buffer[i] = '\0';
			argv[argc] += navodnik;
		} else if(buffer[i] == '\\'){
			if(buffer[i+1] == '\\' || buffer[i+1] == '\"'){
				strcpy(buffer+i,buffer+i+1);
				//previous check for " will not happen
			}
		}
	}
	argv[argc+1] = NULL;
	return argc;
}

int redirector(char* buffer){
	int len = strlen(buffer);
	int fd = 0;
	for(int i=0; i<len; i++){
		if(buffer[i] == '>'){
			if(buffer[i] == '>'){
				while(buffer[++i] != ' '){}
				fd = open(buffer+i, O_WRONLY | O_APPEND | O_CREAT, 0664);
			} else {
				while(buffer[i++] != ' '){}
				fd = open(buffer+i, O_WRONLY | O_CREAT, 0664);
			}
			buffer[i] = '\0';
			if(fd == -1){ //fail to redirect
				perror(buffer+i+1);
				return 0;
			}
			return fd;
		}
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
	printf(GREEN"%s\n\n", "Welcome!"RESET);
	printf(WHITE"%s\n", "System information "RESET);
	printf("%s-%s\n", system_info.sysname, system_info.release);
	printf("%s-%s\n"RESET, system_info.nodename, system_info.machine );	

}