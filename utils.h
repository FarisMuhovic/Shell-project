#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct Arguments{
	int argc;
	char** argv;
};

void pprompt();

int echo(struct Arguments);

struct Arguments buffer2Vector(char*);