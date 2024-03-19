#include "utils.h"
#include "defines.h"
#include <stdlib.h>
#include <string.h>

struct Arguments buffer2Vector(char *buffer){
	int navodnik = 0; //`'"
	int argc = 0;
	for(int i=0; i!=strlen(buffer); i++){ //while true?
		if(buffer[i] == '\n') break;
		if(buffer[i] == ' ' && navodnik == 0){
			buffer[i] = (char) NULL;
		} else if (buffer[i] == '\"'){
			navodnik ^= 0b001;	
		} else if (buffer[i] == '\''){
			navodnik ^= 0b010;
		} else if (buffer[i] == '`'){
			navodnik ^= 0b100;
		}
	}
	struct Arguments args = {argc, (char**)buffer};
	return args;
}

int echo(struct Arguments in){
	printf("\nargc: %d", in.argc);
	for(int i=0; i!=in.argc; i++){
		printf("%s",in.argv[i]);
	}
}