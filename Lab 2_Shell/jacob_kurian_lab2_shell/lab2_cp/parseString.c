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
@params: str is the command that user enter
getting total number of words from command line*/
int getTotalNumberArgs(char *str){
  int STATE = 0;
  int FOUND = 1;
  int TEMP = 2;
  int SEARCHING =3;
  int DONE = 4;
  int START = 5;
  int size = strlen(str);
  int totalWords = 0;

  STATE = START;
  int i =0;
  char c;
  while(i < size && STATE != DONE){
    c = str[i];

    if(STATE == START && c != ' '){
      STATE = FOUND;
    }

    else if(STATE == FOUND && (c == ' ' || c == '\n' || (i+1) == size ) ){
      totalWords++;
      STATE = SEARCHING;
    }

    else if(STATE == SEARCHING && c != ' '){
      STATE = FOUND;
    }

    if(STATE == FOUND && str[i+1] == '\0'){
      STATE = DONE;
      totalWords++;
    }
    i++;
  }

  return totalWords;
}




/* getting the command line argument from the user
and making a double pointer with each word */

char **getArguments(char *str){
  int totalargs = getTotalNumberArgs(str);
  int len = strlen(str);
  char **args = malloc(totalargs * sizeof(char *));
  for(int i = 0; i < totalargs; i++)
  {
    args[i] = malloc(len+1);
  }
  args[totalargs] = NULL;

  char *p;
  p = strtok(str, " ");
  int i =0;

  while(p != NULL){

    if(i < totalargs)
   {
	args[i] = p;

	}
    p = strtok(NULL, " ,");
    i++;
  }
  return args;
}


/*
This is the function to get the first argument from the command line.
eg: ls > text.txt  First argument will be 'ls'
second argument will be 'text.txt'
*/

char **getFirstArg(char **ptr, char c[]){
int i =0;
while((strcmp(ptr[i], c) != 0))
{
i++;
	if(ptr[i] == NULL)
	{
	printf("Error!\n");
	}
}

char **ptr2 = malloc(sizeof(char *) * i);
for(int j =0; j < i; j++)
{
ptr2[j] = malloc(strlen(ptr[j]) +1);
ptr2[j] = ptr[j];
}
ptr2[i] = NULL;

return ptr2;

}

/*
Above function is much more efficient.
This function has the same capability like the 'getFirstArg' function
This is the function to get the first argument from the command line.
eg: ls > text.txt  First argument will be 'ls'
second argument will be 'text.txt'
*/
char **gettingFirstArgument(char **ptr, int size){
int len = getStringLength(ptr);
//printf("Length: %d\n", len);
char **ptr2 = malloc( (size+2) * sizeof(char*));

for(int j =0 ; j <= size+1; j++)
{
  ptr2[j] = malloc(sizeof(char **) * (len+1));
}
int i;
    for(i =0; i <size; i++){
      ptr2[i] = ptr[i];
  }
  ptr2[i] = NULL;

  return ptr2;
}


/*
This is the function to get the second argument from the command line.
eg: ls > text.txt  First argument will be 'ls'
second argument will be 'text.txt'
*/
char **getSecondArgument(char **ptr, int start, int final){
int len = getStringLength(ptr);
int size = (final - start) + 1;
//printf("size of arg2 %d\n",size );
int i;
  char **ptr2 = malloc( size* sizeof(char*));
  for(int j = 0; j < size-1; j++){
  ptr2[j] = malloc(sizeof(char) * (len+1));
}
  for(int i =0; i <size-1; i++){
    ptr2[i] = ptr[start];
    start++;
  }
  ptr2[i] = NULL;
  return ptr2;
}

int getStringLength(char **ptr){
int len= 0;
for(int i = 0; ptr[i] != NULL; i++){

len += strlen(ptr[i]);
}
return len;
}
