#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "defines.h"

void remember(char *buffer){
	FILE *file;
	char line[BUFF_LEN]; // this will cause a buffer overfow
	int lnNum = 0;

	file = fopen(HISTORY_FILE, "r");
	if (file != NULL){
		while (fgets(line, sizeof(line), file)){
			lnNum++;
		}
		fclose(file);
	}

	file = fopen(HISTORY_FILE, "a");
	if (file == NULL){
		printf("Error opening file %s for appending.\n", HISTORY_FILE);
		return;
	}

	fprintf(file, "%d: %s", lnNum, buffer);
	fclose(file);
}

int history(){
	FILE *file;
	char line[BUFF_LEN]; // this will cause a buffer overfow
	file = fopen(HISTORY_FILE, "r");
	if (file != NULL){
		while (fgets(line, sizeof(line), file)){
			printf("%s",line);
		}
		fclose(file);
	}
	return 0;
};