#include "lab4.h"

int getFreeFatChain(FILE *fp, int rdposition, struct FatVariables fatVar, struct RootDirectVarLen rootDirecVar,int startFat,  int rdCluster, int fatSize){
int fatChainNumber = -1;
int num = -1;
char *validstr;
int position = startFat;
char buff[20];
char *buff2;
// find the free fat chain
while(num != 0){
num = getFatValues(fp, position, fatVar,  1,-1, -1);
fatChainNumber +=1;
position+= fatSize;
}
printf("Free fat chain found at %d\n", fatChainNumber);
//updating fat chain's valid bytes and index number
snprintf(buff,sizeof(buff), "%0x", fatChainNumber);
buff2 = formatString(buff, fatVar.fatIndex);
//printf("fatIndex value : %d \n", fatVar.fatIndex);
updateFatVariable(fp, getFCByteLocation(fatChainNumber), fatVar, "1", "000", "000");
getFatValues(fp, getFCByteLocation(fatChainNumber), fatVar,  -1,-1, 1);
//updating Root directory
if(rdposition != -1){
snprintf(buff,sizeof(buff), "%0x", fatChainNumber);
buff2 = formatString(buff, rootDirecVar.startFatChainBytes);
//printf("Updating RD fat chain %s at position : %d\n",buff2, position );
updateVariableRoot(fp, rdposition, rootDirecVar, NULL, NULL, NULL, NULL,
     NULL, NULL, "000000", buff2, NULL, NULL);
   }
//printf("Poiter to Data : %s\n", buff2);

return fatChainNumber;
}


void updateFatVariable(FILE *fp, int seek, struct FatVariables fatVar, char validity[], char fatIndex[], char dataSize[]){

  if(validity != NULL){
    fileWriter2(fp, seek, validity);
  }
  seek+= fatVar.validity;

if(fatIndex != NULL){
  fileWriter2(fp, seek, fatIndex);
}
  seek+= fatVar.fatIndex;

  if(dataSize != NULL){
    fileWriter2(fp, seek, dataSize);
  }
  seek+= fatVar.dataSize;

}

void writeToData(FILE *fp,  int seekpoint, char str[]){
//fileWriter2(fp, int seekpoint, char str[]);
}


int getFatValues(FILE *fp, int position, struct FatVariables fatVar, int validity, int fatIndex, int dataSize){
int x;
int len;
char buff[20];
int startByte = position;
 //printf("~~ From get fun Root Directory ~~ #%d\n", position);

if(validity != -1){
  len = fatVar.validity;
  fseek(fp,position,SEEK_SET);
  fread(buff, sizeof(char), len, fp);
   x = (int) strtol(buff, (char **)NULL, 16);
  // printf(" Posotion: %d validity ~~~~ %d\n", position, x);

	return x;
  }
  position += fatVar.validity;

  if(fatIndex != -1){
    len = fatVar.fatIndex;
    fseek(fp,position,SEEK_SET);
    fread(buff, sizeof(char), len, fp);
     x = (int) strtol(buff, (char **)NULL, 16);
    // printf(" fatIndex ~~~~ %d\n", x);
  	return x;
    }
    position += fatVar.fatIndex;
if(dataSize != -1){
  len = fatVar.dataSize;
  fseek(fp,position,SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  x = (int) strtol(buff, (char **)NULL, 16);

  //printf("pointerToData~~~~ %d\n", x);
  return x;
   }
}
