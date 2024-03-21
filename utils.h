#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void pprompt();

int echo(int argc, char** argv);

int buffer2Args(char*, char**);