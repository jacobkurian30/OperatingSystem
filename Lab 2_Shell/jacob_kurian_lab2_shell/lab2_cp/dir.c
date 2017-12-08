#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <math.h>
#include "myshell.h"


#define MAX_PATH_LENGTH 512
/*
@param: argv contain the dir function its path
This function check the wheather user pass a
path or not. Do appropriate operations based 
on that.
*/

void dirCall(char **argv){
int x ;
//getting the file name
char *pathname = argv[1];

if(argv[1] != NULL)
{
     printf("inside");
	if(is_dir(pathname) != 0){
	    print_decendants(pathname,0);
	}
}
else{

     printf("Outside");

        if(is_dir(".") != 0){
           print_decendants(".",0);
        }
    }

}
/*
This function is print alll the files and directories that present in
the current folder.
*/

void print_decendants(char *pathname, int depth){
int size;
int count;
  if(is_dir(pathname)){
    count =0;
    int *ptr;
    DIR *d;
    struct dirent *p;
    char path[MAX_PATH_LENGTH];
    if((d = opendir(pathname)) == NULL){
     fprintf( stderr, "opendir %s %s\n", path, strerror(errno));
      return;
    }
    while((p = readdir(d)) != NULL)
    {
        if(strcmp(".", p->d_name) == 0 || strcmp("..", p->d_name) == 0)
        continue;
       // make_space(depth*SPACE_PER_INDENT_LEVEL);
      struct stat st;
      stat(path, &st);
      count++;
      // putting together that string to make the path
      snprintf(path, MAX_PATH_LENGTH, "%s/%s", pathname, p->d_name);
      printf("%s\n",p->d_name );
    }
    struct stat st;
    stat(path, &st);
  }
}

/*
This function will check the directory is valid or not
*/

int is_dir(char *path_name)
{
  int size;
  struct stat buff;
    if(stat(path_name, &buff) < 0)
    {
      printf("Error path you passed!\n");
      return 0;
    }
    else{
      size = buff.st_size;
    return S_ISDIR(buff.st_mode);
}
}
