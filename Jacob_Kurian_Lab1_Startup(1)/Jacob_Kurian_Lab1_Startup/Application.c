
//Jacob Kurian
//09/13/2016
//CIS : 3207
//Section: 003

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char* fileReader(FILE *fp, int randomSet);

int main(){


struct timeval tv;
gettimeofday(&tv, NULL);
printf("Start time of the Application     : %ld : %ld\n", tv.tv_sec, tv.tv_usec);
//printf("%ld  %ld\n", tv.tv_sec, tv.tv_usec);
srand(time(NULL));

for(int q =0 ; q < 100; q++){
  // open the a text file to write.
FILE* fp = fopen("textfile1.txt", "w");
// char array to hold all the alphabets
char char_array[26] = {'a', 'b', 'c','d', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l','m','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// creating an array of 10 arrays
char string_Array[10][121];
int a =0;
int i, j;

int randomNum;

// to create each 10 sets
for( i =0; i < 10; i++){
  // creating each sets with random letters
  for( j = 0 ; j < 120 ; j++){
    randomNum = rand()%26;
    string_Array[i][j] = char_array[randomNum];
    a++;
  }

  string_Array[i][j] = '\0';
  // writing the string to the file
  fwrite(string_Array[i], sizeof(char), 120, fp);
}
// closing the file
fclose(fp);

// creatinf random set Number
int randomSet = rand()%10;
// calling the fileReader to get the random set from the file.
char *readFromFile = fileReader(fp, randomSet);
// comping the the set from the file with set from the memory
int val = strcmp(string_Array[randomSet],readFromFile);

/*
This code is for testing purposes.
To make sure the set copied from the file is same as the set in the memory
*/
/*
if(val == 0)
{
printf("same\n" );
}
else
{
  printf("Different\n");
} */


// to free the string from fileReader
free(readFromFile);
remove("textfile1.txt");
}

}


/* This method will get the random set from file.
    And  return a string*/
char* fileReader(FILE *fp, int randomSet){
  fp = fopen("textfile1.txt", "r");
// using fseek to reach the appropriate position in the text file
  fseek(fp, (randomSet * 120), SEEK_SET);
//creating the string with malloc
  char *buffer = malloc(121);
  fread(buffer, 120, 1, fp);
//  printf("Set %d\n", (randomSet+1));
  //printf("\n%s\n",buffer);
  fclose(fp);
  return buffer;
}
