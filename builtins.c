#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

int echo(int argc, char** argv){
	for(int i=1; i<=argc; i++){
		printf("%s ",argv[i]);
	}
	return 0;
}

int cp(int argc, char ** argv){
	if(argc < 2){
		printf("Usage: \t%s <SRC FILE> <DST FILE>\n\t%s ...<MULTIPLE FILES>... <DST FOLDER>", argv[0], argv[0]);
		return -1;
	}
	if(argc == 2){ //file to file
		int src = open(argv[1], O_RDONLY);
    	if (src == -1) {
    	    perror("Error opening SRC");
    	    return -1;
    	}
    	int dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	if (dst == -1) {
    	    perror("Error copying to DST");
    	    return -1;
    	}

    	off_t len = lseek(src, 0, SEEK_END);
    	lseek(src, 0, SEEK_SET);
    	ssize_t bytes_copied = copy_file_range(src, NULL, dst, NULL, len, 0);
    	if (bytes_copied == -1) {
    	    perror("Error in syscall copy_file_range");
    	   return -1;
    	}
    	printf("Copied %zd bytes", bytes_copied);
    	close(src);	close(dst);
    	return 0;
	}
	return 0;
}
