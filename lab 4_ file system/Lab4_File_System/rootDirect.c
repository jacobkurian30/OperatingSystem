#include "lab4.h"

char* getRootDirect(FILE *fp, int position, struct RootDirectVarLen rootStruct, int validity, int nameLen, int name, int fileType, int cDate,
  int mDate, int fsize, int startClusterFatBytes, int ptrRD, int ptrRDChild){
int x;
int len;
char* buff;
int startByte = position;
 //printf("~~ From get fun Root Directory ~~ #%d\n", position);

if(validity != -1){
  len = rootStruct.validity;
  buff =  malloc(len);
  fseek(fp,position,SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
//printf("~~~~~~~~~%c\n", buff[2]);
	return buff;
  }
  position += rootStruct.validity;

if(nameLen != -1){
  len = rootStruct.nameLength;
  buff = malloc(len);
  fseek(fp,position,SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
  //printf("~~~~ %s\n", buff);
  return buff;
   }
  position += rootStruct.nameLength;

if(name != -1){
   startByte = startByte+ rootStruct.validity;
  // char fileNameLength[4] = getString(fp, startByte, rootStruct.nameLength);
   int fileLen = infoPrinter(fp, startByte, rootStruct.nameLength);
//int fileLen = strlen(name);
   //printf("Length of file name : %d\n", fileLen);
   fseek(fp, position, SEEK_SET);
   buff = malloc(fileLen);
   buff = getString(fp, position, fileLen);
  // printf("file Name: %s %d\n" ,buff , fileLen);
   return buff;
  }
  position += rootStruct.fileName;

if(fileType != -1) {
  len = rootStruct.filetype;
  buff = malloc(len);
  fseek(fp,position,SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
  //printf("File Type: %s\n", buff);
  return buff;
}
  position += rootStruct.filetype;

if(cDate != -1){
  len = rootStruct.createdDate;
  buff = malloc(len);
  fseek(fp, position, SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
  //printf("File created Date: %s\n", buff);
  return buff;
}

  position+=rootStruct.createdDate;

if(mDate != -1){
  len = rootStruct.modifiedDate;
  buff = malloc(len);
  fseek(fp, position, SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
  //printf("File modified Date: %s\n", buff);
  return buff;
}

 position+=rootStruct.modifiedDate;

if(fsize != -1){
  len = rootStruct.fileSize;
  buff = malloc(len);
  fseek(fp, position, SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
//  printf("RD cluster number: %s\n", buff);
  return buff;
}
position += rootStruct.fileSize;

if(startClusterFatBytes != -1){
  len = rootStruct.startFatChainBytes;
  buff = malloc(len);
  fseek(fp, position, SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
//  printf("Start Cluster Fat Byte: %s\n", buff);
  return buff;
}
position +=rootStruct.startFatChainBytes;

if(ptrRD != -1){
  len = rootStruct.ptrSiblingDirec;
  buff = malloc(len);
  fseek(fp, position, SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
//  printf("RD cluster number: %s\n", buff);
  return buff;
}
position+= rootStruct.ptrSiblingDirec;

if(ptrRDChild != -1){
 len = rootStruct.ptrChild;
  buff = malloc(len);
  fseek(fp, position, SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
  //printf("RD Child of the Direc: %s\n", buff);
  return buff;
}

}


char* getString(FILE *fp, int seek, int stringlen){
  char* buff = malloc(stringlen+1);
  fseek(fp, seek, SEEK_SET);
  fread(buff, sizeof(char), stringlen, fp);
  buff[stringlen] = '\0';
  return buff;
}
