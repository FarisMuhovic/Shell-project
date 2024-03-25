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

	fprintf(file, "%d: %s\n", lnNum, buffer);
	fclose(file);
}

int recall(){
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
}
int history(int argc, char ** argv)
{
   if (argc == 0) {
	 recall();
   } else if (strcmp(argv[1], "--l") == 0){
   FILE *file;
   char line[BUFF_LEN];
	file = fopen(HISTORY_FILE, "r");
	if (file != NULL){
		int i = 0;
		while (fgets(line, sizeof(line), file)){
			i++;
		}
		int k = 0;
		fseek(file,0,SEEK_SET);
		while (fgets(line, sizeof(line), file)){
			if (i - strtol(argv[2], NULL, 10) <= k) {
				printf("%s",line);
			}
			k++;
			// printf("%d\n", i);
		}
		fclose(file);
	}
	return 0;
   } else {
	return 1;
   }
};