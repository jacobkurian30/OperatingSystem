//Jacob Kurian.
//Lab 2 Shell
// 10/11/2016
#include <signal.h>
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
int getEndNum(char **ptr, int size, char symbol[]);
int countOfRedirectional(char **ptr);
void runpipe(int fd[], char **firstArg, char **secondArg);
void  newPipe(char **ptr, int size);
void inpputer(char **ptr, char **ptr2,  int i);
void batchfile(int argc, char *argv[]);
int pipingCheck(char **ptr);
void inputOutput(char **ptr, char **ptr2,  int i);
int pipef(char **ptr, int size);
void pipeConnector(char **ptr2, char **ptr3);
void newPipe(char **ptr, int size);
void pipeBuiltin(char **ptr, int num, int state);


int main(int argc, char *argv[]){
int batchState = 0;
FILE *batchfile;
/*
checking wheather user passed a batch file or not
*/
if(argc > 1 && (batchfile = fopen(argv[1], "r")) != 0){
batchState = 1;
}

//getting path name
getPathName();
char **ptr;
//The flag for background processor
int processorType;
int backgroundProcess = 0;
int normalProcess = 1;
int unknown =3;
processorType = unknown;
//The flag for piping and input/ouput redirection
int pipestate ;
int normal =1;
int piped = 2;
pipestate = normal;
int totalWords;
//flag for wheather each program done or not
int programStatus;
int notDone =0;
int done=1;
programStatus = notDone;
/*creating a while so that terminal will ask
for new commands again and again*/
while(1){


  	if(pipestate == piped)
  	{
  	  wait(NULL);
  	  pipestate = normal;
    	}

int size2;
char str[100];
int size = 100;

if(batchState == 1){
if(fgets(str, 100, batchfile) == NULL){
batchState =0;
getPathName();
}
else{
size2 = strlen(str);
str[size2 -1] = '\0';
//printf("-------String ---------- %s", str);
}

}

if(batchState == 0)
gets(str);

	if(strlen(str)> 0) {
  /*
   getting tottal number of Argument that user enter
  'getTotalNumberArgs' function is in the parseString.c file
  */
    totalWords = getTotalNumberArgs(str);
    /*
     'getArguments' will take the user input and parse it and return a double char array
    'getArguments' function is in the parseString.c file*/

	 ptr = getArguments(str);

    /*
    checking wheather the user input has input/output redirection
    or the piping. If there is piping involved the 'pipingCheck() function will
    return 1 . If there is not piping involved it will return 0
    'pipingCheck' is inside the piping.c file
    */
    int pipeValue = pipingCheck(ptr);

if(processorType == backgroundProcess)
  wait(NULL);

/*
checking the processorType, either it is background process or
normal process*/
if(strcmp(ptr[totalWords -1], "&") == 0){
  processorType = backgroundProcess;
  *(&ptr[totalWords-1]) = NULL;
  totalWords--;
  //printf("------checking-----\n" );
    }
else
   {
  processorType = normalProcess;
//  printf("normal-----\n");
     }

if(pipeValue == 1){
 // printf("There is piping Involved\n");
    }

    /* The following coding only execuet if there isn't any piping or
    input/output redirection involved inthe user input.'cd', 'clear',
    'clr', 'environ', 'dir','echo', 'pause' and 'help' are built-in
    commands. All of the above commands are implemented inside
    builtFunction.c. The command for 'help' function is implemented
    inside the 'piping.c' file.
  */

if(pipeValue == 0){
        if(strcmp(str, "cd")==0){
          /*calling the 'changeDirec' from builtFunction.c inorder
           to change the directory*/
              changeDirec(ptr[1]);
              programStatus = done;
       	}
        else if(strcmp(str, "clear")==0){
          /*calling 'screenCleaner' function from  builtFunction.c
          to clean the screen*/
              programStatus = done;
              screenCleaner();
        }
        else if(strcmp(str, "clr")==0){
          /*calling 'screenCleaner' function from  builtFunction.c
          to clean the screen*/
              programStatus = done;
              screenCleaner();
        }
        else if(strcmp(str, "environ")==0){
          /*calling 'getEnvironmental' function from  builtFunction.c
          to get all of the environmental variable*/
              getEnvironmental();
              programStatus = done;

        }
	else if(strcmp(str, "pause") == 0){
	/*Calling methods for puase*/
	     getPause();
	     programStatus = done;
	}
        else if(strcmp(ptr[0], "dir")==0){
	     programStatus = done;
          /*calling 'dirCall' function from  builtFunction.c
          to get list of files and folder presented in the direectory*/
             dirCall(ptr);

        }
        else if(strcmp(str, "echo")==0){
	      echo(ptr);
              programStatus = done;
        }
	/*calling the user manual with more filter */
        else if(strcmp(str,"help")==0 ){
              programStatus = done;
  	      pipestate = piped;
          /*calling 'helpMaualWithMore' function from  'piping.c'
          inorder to print the user manual*/
	      helpMaualWithMore();
	       }

       else if(strcmp(str, "exit")==0){
	      exit(0);
	     }
       else if(programStatus == notDone){
        /*creating the fork*/
               int pid = fork();
        /*creating child processor to execute the commnads*/
            if(pid == 0){
                execvp(ptr[0], ptr);
                printf("Command not found\n");
                exit(0);
             }
              /*parent to accept the commands*/
            else{
                if(processorType == 1)
               {
		//     printf("normalProcess----\n" );
		}
                if(processorType == normalProcess)
                {
                    wait(NULL);
                }
		//checking the batch state
	        if(batchState == 0)
            	{
		getPathName();
		}
	    //setting back the programstatus to default
            programStatus = notDone;
              }
            EXIT_SUCCESS;
        }
	/*
	checking the programing status and batch state
	*/
        if(programStatus == done){
         if(batchState == 0)
	{
	getPathName();
	}
          programStatus = notDone;
        }

      }
	/*
	This is the input/output redirection and  piping implementation of the code.
	*/
      else{
	/*
	builtRedirection is checking what type of redirection is it.
	if '>' it will return 1
	if '<' it will return 2
	if < & > it will return 3
	otherwise it is | piping
	*/
        int commandType = builtRedirection(ptr);
	int count= countOfRedirectional(ptr);
        int size;
        char **firstArg;
        char **secondArg;

               if(count == 1){
	           //  for(int i =0; ptr[i] != NULL; i++)
	             //    printf("%s\n",ptr[i] );
              int numState;
               int singleForward =0;
               int doubleForward= 1;
               int i =0;
                   while(ptr[i] != NULL)
                   {
                     if(strcmp(ptr[i], ">") ==0)
                     numState = singleForward;
                     if(strcmp(ptr[i], ">>") == 0)
                     numState = doubleForward;
                     i++;
                   }
                   if(numState == singleForward){
        	               if(commandType == 1){
                            	pipeBuiltin(*(&ptr), totalWords, numState);
			                         if(strcmp(ptr[0],"help") == 0)
				                           pipestate = piped;
		               }
		                else{
	                        size = getEndNum(ptr, totalWords, ">");
		        	 // firstArg = gettingFirstArgument(ptr,size);
				 firstArg = getFirstArg(ptr, ">");
		                 secondArg = getSecondArgument(ptr, size+1, totalWords);
        	                 outputter(firstArg, secondArg, size);
		                               }
	            }
                  else{
	                   if(commandType == 1){
                                pipeBuiltin(*(&ptr), totalWords, numState);
			                     if(strcmp(ptr[0],"help") == 0)
                           		     pipestate = piped;
	                    }
                            else{
                                size = getEndNum(ptr, totalWords, ">>");
                                //firstArg = gettingFirstArgument(ptr,size);
                                firstArg = getFirstArg(ptr, ">>");
				secondArg = getSecondArgument(ptr, size+1, totalWords);
                                outputterAppend(firstArg, secondArg, size);
       		                     }
	                            }
        }
        else if(count == 2){
     	//	printf("----------State : 2----------\n");
	    size = getEndNum(ptr, totalWords, "<");
        //  firstArg = gettingFirstArgument(ptr,size);
	firstArg = getFirstArg(ptr, "<");
          inpputer(ptr,firstArg, size);
        }
        else if(count == 3){
          size = getEndNum(ptr, totalWords, "<");
         // firstArg = gettingFirstArgument(ptr,size);
          firstArg = getFirstArg(ptr, "<");
          inputOutput(ptr, firstArg, size);
        }
        else{
          size = getEndNum(ptr, totalWords, "|");
          printf("found at %d\n",size );
         // firstArg = gettingFirstArgument(ptr,size);
          firstArg = getFirstArg(ptr, "|");
	        secondArg = getSecondArgument(ptr, size+1, totalWords);
          pipestate = piped;
          pipingfuntion(firstArg, secondArg);
        }
        if(batchState ==0)
{
	getPathName();}
}

}

else{
if(batchState == 0)
{ getPathName(); }
  }
    }
}

/*
@params ptr = parsed user command
@parasms num = the index number of redirection symbol
@params state = 0 means trucate the file
state = 1 means append the file
This is the input/output redirectional methods for al the built-in commands
*/

void pipeBuiltin(char **ptr,  int num, int state){
//printf("------------Inside STATE-----------------------------\n");
int saveOut = dup(1);
int fd;
  if(strcmp(ptr[0], "dir")==0){
	  if(state == 0){
			if(ptr[3] != NULL)
	      		{
			fd = open( ptr[3], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
		 	}
			else{
			ptr[1] = NULL;
			fd = open( ptr[2], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
			}
		}
	else if(state != 0 && ptr[3] != NULL )
		 fd = open( ptr[3], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
	  else
	     {
		ptr[1] = NULL;
		 fd = open( ptr[2], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
     		}
     dup2(fd, STDOUT_FILENO);
     dirCall(ptr);
	}
  else if(strcmp(ptr[0],"echo")== 0){
	  if(state == 0)
	     fd = open(ptr[num-1], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
	  else
        fd = open(ptr[num-1], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
     dup2(fd, STDOUT_FILENO);
     echo(ptr);
  }
  else if(strcmp(ptr[0],"environ") == 0){
  	if(state == 0)
  	   fd = open( ptr[2], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
  	else
  	   fd = open( ptr[2], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
     dup2(fd, STDOUT_FILENO);
     getEnvironmental();
  }
  else if(strcmp(ptr[0],"help") == 0){
  	if(state == 0)
      	   fd = open( ptr[2], O_WRONLY| O_CREAT |O_TRUNC, S_IRUSR | S_IWUSR);
    	else
           fd = open( ptr[2], O_WRONLY| O_CREAT |O_APPEND, S_IRUSR | S_IWUSR);
    dup2(fd, STDOUT_FILENO);
    helpMaualWithMore();
}
  else{

      printf("Error in the Command\n");
  }

dup2(saveOut, STDOUT_FILENO);
close(fd);
}

/*
@param : ptr = parsed user command
This function will tell the program what type of redirection or piping
that user is trying to do
*/

int countOfRedirectional(char **ptr){
int STATE;
int INITIAL =0;
int FORWARD = 1;
int BACKWARD =2;
int BOTH =3;
int PIPING = 4;
STATE = INITIAL;
int i =0;
while(ptr[i] != NULL){
      if((strcmp(ptr[i], ">") ==0  || strcmp(ptr[i], ">>") == 0 ) && STATE == INITIAL)
        STATE = FORWARD;
      else if(strcmp(ptr[i], "<") ==0 && STATE == INITIAL)
        STATE = BACKWARD;
      else if((strcmp(ptr[i], ">") ==0  || strcmp(ptr[i], ">>") == 0 ) && STATE == BACKWARD)
        STATE = BOTH;
      else if(strcmp(ptr[i], "<") ==0 && STATE == FORWARD)
        STATE = BOTH;
  i++;
  }

      if(STATE == INITIAL)
        STATE = PIPING;
return STATE;
}

/*
@param: ptr = parsed user command
checking the user command has input/ouput redirection or piping
*/

int pipingCheck(char **ptr){
int returnVal = 0;
int i =0;
  while(ptr[i] != NULL){
    if((strcmp(ptr[i], "|")) == 0 || (strcmp(ptr[i], ">")) == 0 || (strcmp(ptr[i], "<")) == 0 || (strcmp(ptr[i], ">>")) == 0){
      returnVal =1;
    }
  i++;
  }
return returnVal;
}

/*
@params: ptr  = parsed user command
@oarams: symbol = redirectional symbol such as > , < , |
The function will return the position of redirection symbol
*/
int getEndNum(char **ptr, int size, char symbol[]){
int i =0;
  while(ptr[i] != NULL){
    if(strcmp(ptr[i],symbol) == 0)
    break;
    i++;
  }
return i;
}
