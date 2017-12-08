#include<sys/stat.h>
#include <dirent.h>
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<limits.h>
#include"myshell.h"
#define KRED "\x1B[31m"

/*
The following function will get the hostname and pathname of the 
current directory that user is interacting. The hostname will be in
blue and pathname will be in red. 
*/
void  getPathName(){
  char hostName[PATH_MAX];
  char pathName[PATH_MAX];
  getcwd(pathName, sizeof(pathName));
  gethostname(hostName, sizeof(hostName));
    printf("\x1b[34m%s\x1b[0m:\x1b[32m%s\x1b[0m$ ", hostName,pathName );

}
