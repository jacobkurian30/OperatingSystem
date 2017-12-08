#include "lab4.h"

char* getDateTime(){
time_t t = time(NULL);
struct tm time = *localtime(&t);
struct tm buf;
//local time
char *s = asctime(localtime(&t));
//printf("Size of : %zu Length: %zu  %s\n", sizeof s, strlen(s), s);
return s;
}

char* formatString(char str[], int intentLen){
  char *result = malloc(intentLen+1);
  int len = strlen(str);
  char buff[16];
  if(intentLen ==  (len )){
    strcpy(result, str);
  }
  else if(intentLen < len){
      printf("*******From format String: Error in formatting ******** %d %d %s\n", intentLen, len, str);
  }
  else{
    int val = intentLen - (len);
//printf("Inside Last else ================================================================ %d %d %s\n", intentLen , len , result);
    for(int i = 0; i < val ; i++){
      if(i == 0)
    {  strcpy(buff,"0");
  }
  else{
      strcat(buff, "0");
}
    }
    strcpy(result, buff);
    strcat(result, str);
  }

  //printf("Result--------------------------------------- %s\n",  result);

  return result;
}


void updateVariableRoot(FILE *fp, int seek, struct RootDirectVarLen rootStruct, char validity[], char nameLen[], char name[], char fileType[],
   char cDate[], char mDate[], char fileSize[], char startFatClus[],char ptrNextClust[],char ptrChild[]){


if(validity!= NULL){
fileWriter2(fp, seek, validity);
}
seek += rootStruct.validity;

if(nameLen != NULL){
fileWriter2(fp, seek, nameLen);
}
seek+=rootStruct.nameLength;

if(name != NULL){
  fileWriter2(fp,seek, name);
}
seek+=rootStruct.fileName;

if(fileType != NULL){
  fileWriter2(fp, seek, fileType);
}
seek+= rootStruct.filetype;


if(cDate != NULL){
  fileWriter2(fp, seek, cDate);
}
seek+=rootStruct.createdDate;

if(mDate != NULL){
  fileWriter2(fp, seek, mDate);
}
seek+=rootStruct.modifiedDate;

if(fileSize != NULL){
  fileWriter2(fp, seek, fileSize);
}
seek+=rootStruct.fileSize;

if(startFatClus != NULL){
  fileWriter2(fp, seek, startFatClus);
}
seek+=rootStruct.ptrSiblingDirec;


if(ptrNextClust != NULL){
  fileWriter2(fp, seek, ptrNextClust);
}
seek+=rootStruct.ptrChild;

if(ptrChild != NULL){
  fileWriter2(fp, seek, ptrChild);
}
}
