#include<sys/stat.h>
#include <dirent.h>
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include "myshell.h"


/*
This mathod will pass the input from a text file to a executable or
a command and pass the out of the file to a text file. If the file that
passing the input do not exist, the user will get a error message.
Parameters: ptr is the parse double array of the user input.
ptr2 is the first command or the executable file that user passed in.
*/

void inputOutput(char **ptr, char **ptr2,  int i){
int state ;
int singleForward = 0;
int doubleForward = 1;
  if(strcmp(ptr[i+2], ">") == 0)
 {
   state = singleForward;
 }
 else if(strcmp(ptr[i+2], ">>") == 0)
 {
  state = doubleForward;
 }
  int pid = fork();
    if(pid == 0){
      int fd = open( ptr[i+1], O_RDONLY , S_IRUSR | S_IWUSR);
          if(fd != -1){
            int fd2;
            dup2(fd, STDIN_FILENO);
              if(state == singleForward)
                  fd2= open( ptr[i+3], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
                else
                  fd2= open( ptr[i+3], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
          dup2(fd2, STDOUT_FILENO);
          execvp(ptr2[0], ptr2);
          printf("Error in Command \n");
          exit(0);
        }
      else{
          printf("%s: There is no such file or directory\n",ptr[i+1] );
        	exit(0);
	}
    }
  else{
        wait(0);
    }
}

/*
This method will pass the input to a command or a executable from
a text file. If the file does not exit,  user will get an error
message.
*/

void inpputer(char **ptr, char **ptr2,  int i){
  int pid = fork();
    if(pid == 0){
      int fd = open(ptr[i+1], O_RDONLY , S_IRUSR | S_IWUSR);
          if(fd != -1){
      //    printf("Number:  %d\n", fd);
          dup2(fd, STDIN_FILENO);
          execvp(ptr2[0], ptr2);
          printf("Error in Command \n");
          exit(0);
        }
        else{
          printf("%s: no such file or directory\n",ptr[0] );
	  exit(0); 
	}
    }
    else{
        wait(0);
    }
}

/*
'outputter' function will take the the output of a command or executable
and redirect it into a text file. This function will create a new file
if the file does not exist. If the file that user passed already exist,
this function will truncate the file into lenght zero and add the new
output.
*/
void outputter(char **ptr, char **ptr2, int i){
  int pid = fork();
  if(pid ==0){
// int fd = open( ptr3[0] , O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
    int fd = open( ptr2[0], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
    dup2(fd, STDOUT_FILENO);
    execvp(ptr[0], ptr);
    printf("Error in Command \n");
    exit(0);
  }
  else{
    wait(0);
  }
}
/*
'outputterAppend' function will take the the output of a command or executable
and redirect it into a text file. This function will create a new file
if the file does not exist. If the file that user passed already exist,
this function will append the new output to the file.
*/
void outputterAppend(char **ptr, char **ptr2, int i){
  int pid = fork();
  if(pid ==0){
    int fd = open( ptr2[0], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
    dup2(fd, STDOUT_FILENO);
    execvp(ptr[0], ptr);
    printf("Error in Command \n");
    exit(0);
  }
  else{
    wait(0);
  }
}
