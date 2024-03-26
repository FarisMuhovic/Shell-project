#define _GNU_SOURCE
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
	getcwd(path, 128);
	char machinenamef[64];
	gethostname(machinenamef, 64);
	char concatedpath[150];
	sprintf(concatedpath, "/home/%s", getlogin());
	if(strncmp(path, concatedpath, strlen(concatedpath)) == 0){
		sprintf(concatedpath, "~%s", path + strlen(concatedpath));
	} else{
		strlcpy(concatedpath, path, 128);
	}

	sprintf(prompt, GREEN"%s"WHITE"@"GREEN"%s:"BLUE"%s"WHITE"$ "RESET, getlogin(), machinenamef, concatedpath);
	return prompt;
}

int buffer2Args(char* buffer, char** argv){
	int argc = 0;
	int navodnik = 0;//bool
	int len = strlen(buffer);
	argv[0] = strtok(buffer, "\n");
	for(int i = 0; i < len; i++){
		//exit if max args reached??
		if(buffer[i] == ' ' && !navodnik){
			buffer[i] = '\0';
			while(buffer[++i] == ' '){
				buffer[i] = '\0'; //also remove extra spaces
			}
			argv[++argc] = buffer + i;
		} else if(buffer[i] == '\"'){
			navodnik = !navodnik;
			buffer[i] = '\0';
			argv[argc] += navodnik;
		} else if(buffer[i] == '\\'){
			if(buffer[i + 1] == '\\' || buffer[i + 1] == '\"'){
				strlcpy(buffer + i, buffer + i + 1, BUFF_LEN);
				//previous check for " will not happen
			}
		}
	}
	if(strlen(argv[argc]) == 0){ //should not have to do this.
		argc--;// this is because the code above does not work properly.
	}
	argv[argc + 1] = NULL; //just in case
	return argc;
}

int redirector(char* buffer){
	int fd;
	for(int i = 0; buffer[i] != '\0'; i++){
		if(buffer[i] == '>'){
			buffer[i++] = '\0'; //set to null and go to next one
			if(buffer[i] == '>'){
				i++;//skip the >
				while(buffer[i] == ' '){ i++; }//this works, DO NOT TRY TO OPTIMIZE IT
				fd = open(buffer + i, O_WRONLY | O_APPEND | O_CREAT, 0664);
			} else{
				while(buffer[i] == ' '){ i++; }
				fd = open(buffer + i, O_WRONLY | O_TRUNC | O_CREAT, 0664);
			}
			if(fd == -1){ //fail to redirect
				perror(buffer + i);
				return -1;
			}
			return fd;
		}
	}
	return -1;
}

int handlePipe(char** argv){ //return index of pipe symbol, or 0 if no pipe
	for(int i = 0; argv[i] != NULL;i++){
		if(argv[i][0] == '|'){
			argv[i] = NULL;//argv is still null-terminated
			return i;
		}// old argc is i-1, new argc will be argc-i-1 bc pipe is ignored
	}//old buffer will not change, and new buffer will start at buffer+i+1
	return 0;
}

void printArgs(int argc, char** argv){
	fprintf(stderr, "Arguments: %d\n", argc);
	while(argc >= 0){
		printf("%d: %s\n", argc, argv[argc]);
		argc--;
	}
}


void welcomeText(){
	struct utsname system_info;

	if(uname(&system_info) == -1){
		perror("uname");
	}
	printf(GREEN"%s\n\n", "Welcome!"RESET);
	printf(WHITE"%s\n", "System information "RESET);
	printf("%s-%s\n", system_info.sysname, system_info.release);
	printf("%s-%s\n"RESET, system_info.nodename, system_info.machine);

}