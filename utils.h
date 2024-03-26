#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char* prompt(int);

int buffer2Args(char*, char**);
int redirector(char*);
void printArgs(int, char**);
int handlePipe(char**);
void welcomeText();