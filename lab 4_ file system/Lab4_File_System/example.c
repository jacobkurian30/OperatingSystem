#include <stdio.h>
#include <stdlib.h>

int main(){

char *getContent = malloc(1024+1);
//int dataLocation;
//printf("\033[33;1mFile Name %s : Size: %d.\033[0m\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), fileSize );
//printf("Maximum data you can enter at one time is 1024 bytes.\n");
//printf("If your data is more than that call write funtion couple of times\n");
/*printf("Enter the data: \n");
fgets(getContent, 1024, stdin);
printf("%s\n", getContent);
*/
call();

}


void call(){
char *getContent = malloc(1024+1);
do{
printf("Enter the data: \n");
fgets(getContent, 1024, stdin);
printf("%s\n", getContent);
}while(1);


}
