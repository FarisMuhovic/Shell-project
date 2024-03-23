#pragma once
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char* prompt(int);

int echo(int, char**);

int buffer2Args(char*, char**);

void welcomeText();