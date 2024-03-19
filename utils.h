#pragma once
#include <stdio.h>
#include <unistd.h>

inline void pprompt(){
	printf("%s@%s:%s> ", getlogin(), "machina", getcwd(NULL, 0) );
}