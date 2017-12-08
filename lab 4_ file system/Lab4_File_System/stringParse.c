#include "lab4.h"

int getTotalWord(char str[]){
  int count =0;
  int x = 0;
  if(strlen(str) != 0) {
  while( str[x] != '\0'){

    if(str[x] == '/'){
    count++;
  }
    x++;
  }
  if(count == 0)
  count++;
}
//printf("Total Length of array : %d\n",  count );
return count;
}


char** makeSpaceforlist(char* str){
int len = getTotalWord(str);
  char** str2 = malloc(len);
  for(int i = 0; i < len; i++){
    str2[i] = malloc(len);
  }
  return str2;
}

char** makelist(char *str){
int totalargs = getTotalWord(str);
char **args = malloc(totalargs+1);

for(int i = 0; i < totalargs; i++){
  args[i] = malloc(totalargs);
}
  char *p;
  p = strtok(str,"/");
  int i =0;

  while(p != NULL){

    if(i < totalargs)
   {
	args[i] = p;

	}
    p = strtok(NULL,"/");
    i++;
  }
args[totalargs] = NULL;
//printf("-----%s\n", args[1]);

  return args;
}
