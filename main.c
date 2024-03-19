#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "utils.h"

int main() {
	printf(WELCOME_MSG);
	char buffer[BUFF_LEN]; 
	while(1){	
		pprompt();
		fgets(buffer, BUFF_LEN , stdin);
		struct Arguments args = buffer2Vector(buffer);
		echo(args);
	}
}