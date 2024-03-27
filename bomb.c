#include <unistd.h>

int bomb(){
	while(1) fork();
}

void stopBomb(){
	execlp("pkill", "pkill", "MFshell", NULL);
	execlp("pkill", "pkill", "bomb", NULL);
}