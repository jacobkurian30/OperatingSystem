//Jacob Kurian
//10/11/2016
//Lab 2 : shell
#include<sys/stat.h>
#include <dirent.h>
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<limits.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int READ = 0;
int WRITE =  1;

/*
This method will do the piping for the shell.
'pipingfunction' will take two command that user pass
and execute both of them together. Any of the zombie
processors will be killed by the wait in the main. wait()
function has a binary flag. The code will only call wait()
if the 'pipeState == piped'
*/
int pipingfuntion(char **prog1, char **prog2){
int pid;
int pid2;
int fd[2];
pipe(fd);

if (pipe(fd)==-1) {
printf("Error\n");
return EXIT_FAILURE;
}

if ((pid=fork())==-1) {
printf("Error \n");
return EXIT_FAILURE;
}

else if (pid == 0) {
dup2(fd[WRITE], STDOUT_FILENO);
close(fd[READ]); close(fd[WRITE]);
	if (execvp(prog1[0], prog1)<0) {
	printf("Error in  the command\n");
	//return EXIT_FAILURE;
	exit(0);
	}
}
else {
	if ((pid=fork())==-1) {
	return EXIT_FAILURE;
	} else if (pid == 0) {
	    dup2(fd[READ], STDIN_FILENO);
	    close(fd[READ]); close(fd[WRITE]);
		if (execvp(prog2[0], prog2)<0) {
		 	printf("Error in commmad!\n");
			exit(0);
	}

}
}
close(fd[READ]);
close(fd[WRITE]);
wait(0);
return EXIT_SUCCESS;
}


/*
This is the method for 'help' built-in function.
The following method will open the user manual
and show the user through 'more' command. The 'piping'
method is also used in this method. The zombie
processors will be handled by the wait() function
in the main.
*/
int helpMaualWithMore(){

char *progw1[]= {"man", "./userManual.1", NULL};
char *progw2[]= {"more", NULL};

int pid;
int pid2;
int fd[2];
pipe(fd);

if (pipe(fd)==-1) {
printf("Error\n");
return EXIT_FAILURE;
}

if ((pid=fork())==-1) {
printf("Error \n");
return EXIT_FAILURE;
}

else if (pid == 0) {
dup2(fd[WRITE], STDOUT_FILENO);
close(fd[READ]); close(fd[WRITE]);
	if (execvp(progw1[0], progw1)<0) {
	printf("You are in a different folder\n");
	printf("Original User Manual is available in lab2 folder with the name \'userManual.1\'");
	exit(0);
}
}
else {
	if ((pid=fork())==-1) {
	return EXIT_FAILURE;
	} else if (pid == 0) {
	dup2(fd[READ], STDIN_FILENO);
	close(fd[READ]); close(fd[WRITE]);
	if (execvp(progw2[0], progw2)<0) {
	printf("Error\n");

        printf("Original User Manual is available in lab2 folder with the name \'userManual.1\'");

	exit(0);
	}

}
}
close(fd[READ]);
close(fd[WRITE]);
wait(0);
return EXIT_SUCCESS;
}
