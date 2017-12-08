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
#include "myshell.h"


/*
this command will pause the screen untill user press 'Enter'
*/
void getPause(){
char c;
do{
c = getchar();
}while(c != '\n');

}
/*
@param: ptr = parsed user input
This function work with input/output and pipe portion
in main function. This function will check for built-in 
command.
*/

int  builtRedirection(char **ptr){
int state;
int builtIn =1;
int nonBuiltIn =2;
int i =0;
if(strcmp(ptr[i],"dir")==0 || strcmp(ptr[i], "echo")==0 || strcmp(ptr[i], "environ")==0 || strcmp(ptr[i], "help")==0)
state = builtIn;
else
state = nonBuiltIn;
//printf("STATE : %d\n", state);
return state;
}


/*
@param: ptr = parsed user input
the following function is the built-in for 'echo'
will print what ever user type back to screen
*/

void echo(char **ptr){
int i =1;
        while(ptr[i] != NULL)
        {
          printf("%s ", ptr[i]);
          i++;
		if(ptr[i] != NULL){
                if(strcmp(ptr[i], ">")== 0 || strcmp(ptr[i], ">>") == 0)
                  break;
       }
	 }
printf("\n");
}



/*
This function will print all the environmental strings
*/
void getEnvironmental(){
  extern char **environ;
  for(int i =0; environ[i] != NULL; i++)
printf("%s\n",environ[i] );
//  printf("PATH %s", getenv("PATH"));
}

/*
@param str = path
this function will change path for the user
*/
void changeDirec(char *str){
  chdir(str);
}

/*
this function will clean the screen for user
*/

void screenCleaner(){
  system("clear");
}
