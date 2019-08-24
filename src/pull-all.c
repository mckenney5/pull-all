/* This is free and unencumbered software released into the public domain. See LICENSE for details */

#include <stdio.h>   //printf, puts
#include <dirent.h>  //DIR, readdir, opendir
#include <string.h>  //strcmp, strcpy
#include <unistd.h>  //getcwd
#include <stdlib.h>  //system

//Program Start-Up
#define VER "1.0.0"
#define MOTD "This is free and unencumbered software released into the public domain. See LICENSE for details"

//Max sizes (note NAME_MAX is defined by POSIX for longest file name)
#define DIR_MAX 1000
#define MAX_CMD 1024

//Commands
#define CMD0 "cd "
#define CMD1 "git pull "
#define CMD2 "cd .."

#ifndef NO_COLOR
//Colors
#define GREEN "\x1B[32m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"
#else
//No Colors
#define GREEN ""
#define WHITE ""
#define RESET ""
#endif


int list_dir(char dir_info[][NAME_MAX]){
/* creates a list of dirs in the current working dir */
        char cwd[NAME_MAX] = {'\0'};
        int i=0;
        DIR *d;
        struct dirent *dir;
        d = opendir(getcwd(cwd, NAME_MAX));
        if(!d) return 1;
	while((dir = readdir(d)) != NULL && i < DIR_MAX){
		if(dir->d_type == DT_DIR){
			if(dir->d_name[0] != '.' && dir->d_name[0] != '\0'){
				//copies all dirs, ignores NULL and "." and ".."
				strcpy(dir_info[i], dir->d_name);
				i++;
			}
		}
	}
	closedir(d);
	return 0;
}

long pull(){
/* gets a list of dirs, steps through each one while running CMD1 and CMD2 */
	int i;
	long rval = 0;
	char dirs[DIR_MAX][NAME_MAX] = {'\0'};
	char command[MAX_CMD+NAME_MAX] = {'\0'};

	//gets the list of directories
	if(list_dir(dirs)){
		perror("Error getting dirs.");
		return 1;
	}

	//step through every dir, set up the syntax for the commands, run it, then keep track of the exit code
	for(i=0; i < DIR_MAX && strcmp(dirs[i], "\0"); i++){
		printf("%sUpdating repo '%s%s%s'%s\n", WHITE, GREEN, dirs[i], WHITE, RESET);
		snprintf(command, MAX_CMD+NAME_MAX, "%s%s&& %s&& %s", CMD0, dirs[i], CMD1, CMD2);
		rval += system(command);
	}
	return rval;

}

int main(int argc, char** argv){
	printf("%s [VERSION %s]\n%s\n--\n\n", argv[0], VER, MOTD);
	if(argc > 1){
		fprintf(stderr, "Error: This program does not take command line args.\n");
		return 1;
	} else {
		long out = pull();
		if(out != 0) return -1; //an error may have occured
		else return 0;
	}
}

