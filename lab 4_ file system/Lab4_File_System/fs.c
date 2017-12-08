//Jacob Kurian
//lab 4 : File system
// 12/11/2016
#include "lab4.h"

struct ReservedVarLen{
  int sectorPerCluster;
  int sectorForFat;
  int sectorForRD;
  int numFat;
  int fileSystemType;
  };

  struct ReservedVarLen rsVar;
  volatile struct RootDirectVarLen rootDirecVar;
  volatile struct FatVariables fatVar;

//Total Number of sectors
int totalReservedSector = 1;
int totalFatSector = 55;
int totalDataSector = 8000;
int totalRootDirectory = 8000;


int bytespSector = 512;
int sectorpCluster = 2; // 1024 bytes
int reservedSectorSize = 512;

static int Reservedposition = 0;
//Fat table variables
int startFAT = 512;
int FatChainSize = 7;
int totalFatChain = 4000;

// Data variables
int startData;
int dataSize = 1024;

//Root Directory variables
int rootDirecSize = 94;
int startRootDirectory ;
char buff[100];
char** args;
char option[2];
char str1[10];
int RootSeachLimit = 200;



int main(){
  // calculating the values
  startData = (totalReservedSector * 512) + (totalFatSector * 512);
  startRootDirectory = startData + (totalDataSector * 512);
int index = 0;
printf("Start Root Directory: %d\n", startRootDirectory);
//Opening the file
FILE *fp = fopen("output.dat", "r+");
//calling the funtion to set the values for struct variables
setRootDirectVarLen();
setFatVlues();
int num = 0;
do{
  if(num > 0)
  {
      printf("Error in the format you entered.\n");
  }
printf("Do you want to reset the drive ? yes/no\n");
scanf("%s",buff);
num++;
}while(strcasecmp(buff,"yes") != 0 && strcasecmp(buff,"no") != 0);

/*
asking the user permission to reset the drive*
Also initialting the reserved sector ,  fat ,data , root directory
*/
if(strcasecmp(buff,"yes") == 0){
  printf("Reseting the drive...\n");
    createReservedSector(fp);
    for(int i = 0; i < totalFatChain; i++){
      creatingFat(fp,i);
    }
    Reservedposition = startData;
    for(int i = 0; i< totalFatChain; i++){
      createData(fp, i);
    }
    for(int i = 0; i < totalFatChain; i++){
      createRootDirectory(fp, i);
    }
    initiateRootDirect(fp, startRootDirectory);
}
printf("Name of the Root:  '%s' \n", getRootDirect(fp, startRootDirectory, rootDirecVar, -1, -1, 1, -1, -1,-1,-1, -1, -1, -1));

index = 1;
/*
present a user interface that user all the operation available on file system
*/
do{

if(index == 1){
strcpy(option,selectOption(buff));
//printf("Selection option from main %s\n", option);
getPath(fp, buff, args, option);
index = 0;
}
if(index == -1)
{
  printf("Re-enter : Error in command \n");
}
printf("Do you wanna perform more operations yes/no\n");
scanf("%s",str1);

if(strcasecmp(str1, "no") == 0)
break;
if(strcasecmp(str1, "yes") == 0)
{
  index = 1;
}
else{
  index = -1;
}
}while(strcasecmp(buff,"yes") != 0 && strcasecmp(buff,"no") != 0);
fclose(fp);
return 0;
}

/*
getting the path from the user
*/
void getPath(FILE *fp, char buff[], char** args, char *option){
//  printf("Selection option from main %s\n", option);
if(strcasecmp(option,"a") == 0 || strcasecmp(option,"b")==0 ||  strcasecmp(option, "g")==0 || strcasecmp(option,"c")==0 || strcasecmp(option,"d")==0  || strcasecmp(option,"f")==0 ){
  int x;
  do{
  x = 0;
  printf("Enter the path: \n");
  scanf("%s",buff);
  args = makelist(buff);
  while(args[x] != NULL){
    //printf("~~~ %s\n",args[x] );
    x++;
  }
}while(strlen(args[x-1]) > 15);

}

//printf("Selected choice : %s\n", option);

if(strcasecmp(option,"a") == 0){
addfileAndFolder(fp, args, 0 );
}
else if(strcasecmp(option, "b") == 0){
 addFolder(fp, args);
}
else if(strcasecmp(option,"c") == 0){
  openFile(fp, args, startRootDirectory, rootDirecVar);
}
else if(strcasecmp(option, "d") == 0){
  openFolder1(fp, args, startRootDirectory, rootDirecVar);
}
else if(strcasecmp(option,"e") == 0){
  getList(fp, startRootDirectory);
}
else if(strcasecmp(option,"f") == 0){
  deleteFile(fp, args, startRootDirectory,rootDirecVar);
}
else if(strcasecmp(option,"g") == 0){
  deleteFolder(fp, args, startRootDirectory,rootDirecVar);

}
else if(strcasecmp(option,"h") == 0){
   getDetails(fp, startRootDirectory);
}
else{
  printf("~Re-enter! Wrong Input~\n");
}
}

/*
adding directory to the file system
*/
int addFolder(FILE *fp, char** path){
  int length = 0;
  while(path[length] != NULL){
    length++;
  }
char* sibilingFreeStr;
int  sibilingFreeNum;
int position = startRootDirectory;
int STATE = -1;
int DONE = 4;
int FOUND = 2;
int NOTDONE = 5;
int ERROR = 6;
int index = 0;
int NEXT = 1;
int RUNNING =3;
int limit = 0;
  if(length == 1){
    sibilingFreeNum = -1;

    while(sibilingFreeNum != 0){
      //printf(" Looking for path \n" );

      sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1);
      sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
      //printf("path  number: %d\n", sibilingFreeNum );
      if(sibilingFreeNum == 0){
        STATE = DONE;
        //printf("free path find at position %d\n", position);
        adding_folder(fp, position, path[length-1]);
        addToLinkList(fp, startRootDirectory, position);
      }
      else{
        position += rootDirecSize;
      //  printf("Incremented\n");
      }
    }
  }
  else{

    sibilingFreeNum = -1;
    STATE = RUNNING;
    int index2 = 0;

    sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    //path failed
      if(sibilingFreeNum == 0){
          STATE = ERROR;
        }
      else{
          position = sibilingFreeNum;
          }

    while(STATE != FOUND  && STATE != ERROR & limit <RootSeachLimit ){

    //printf("----------------------------------------> %s %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1) , path[index] );
      if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
          //printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1));
          if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "1") == 0){
          //    printf("-------------------------------------Layer 3 foldertype matched \n");
              STATE = NEXT;
              index++;
                if(path[index+1] == NULL){
                    STATE = FOUND;
                    printf("Path accepted !\n");
                //    sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
                  //  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
                    findFreePath2(fp, startRootDirectory, path, length, rootDirecSize,position);
            }
          }
        }


      if(STATE != NEXT && STATE != FOUND && STATE != ERROR){
        sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
        position = sibilingFreeNum;
        limit++;
        }

        if(STATE == NEXT){
        //  printf("Next  ---- >\n");
          sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
          sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
          position = sibilingFreeNum;
          STATE = RUNNING;
        }
        if(position == 0){
          STATE = ERROR;
        }
    index2++;
        }

      }
      if(STATE == ERROR && STATE != DONE && STATE != FOUND){

        printf("ERROR IN CREATING DIRECTORY!\nWrong path provided\n");

  }
}

/*
This funtion will add files
*/

int addfileAndFolder(FILE *fp, char** path, int fileType){
  int length = 0;
  while(path[length] != NULL){
    length++;
  }
char* sibilingFreeStr;
int sibilingFreeNum;
int position = startRootDirectory;
int STATE = -1;
int DONE = 1;
int limit = 0;
int index = 0;
int NEXT = 5;
int FOUND = 2;
int RUNNING =3;
int ERROR =4;
  if(length == 1){
    sibilingFreeNum = -1;

    while(STATE != DONE && limit < RootSeachLimit ){
      //printf(" Looking for path \n" );
      if(sibilingFreeNum == 0){
            STATE = DONE;
            //printf("free path find at position %d\n", position);
            adding_file(fp, position, path[length-1]);
            addToLinkList(fp, startRootDirectory, position);
            STATE = DONE;
      }
      else{
            sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1);
            sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
            if(sibilingFreeNum == 0){
          //      printf("find free entry \n");
              }
            else{
                position += rootDirecSize;
        //        printf("Incremented\n");
                limit++;
              }
      }

    }
  }

else{
sibilingFreeNum = -1;
STATE = RUNNING;
int index2 = 0;

sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
//path failed
  if(sibilingFreeNum == 0){
      STATE = ERROR;
    }
  else{
      position = sibilingFreeNum;
      }

while(STATE != FOUND  && STATE != ERROR & limit <RootSeachLimit ){

//printf("----------------------------------------> %s %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1) , path[index] );
  if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
      //printf("-------------------------------------Layer 2 name matched %s %s\n",path[index], getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
      if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "1") == 0){
    //      printf("-------------------------------------Layer 3 foldertype matched \n");
          STATE = NEXT;
          index++;

            if(path[index+1] == NULL){
                STATE = FOUND;
                printf("Path accepted\n");
            //    sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
              //  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
                position = findFreePath(fp, startRootDirectory, path, length, rootDirecSize,position);
        }
      }
    }
  if(STATE != NEXT && STATE != FOUND && STATE != ERROR){
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    position = sibilingFreeNum;
    limit++;
    }
    if(STATE == NEXT){
      //printf("From add file : getting Next index  ---- >\n");
      sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
      sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
      position = sibilingFreeNum;
      STATE = RUNNING;
    }
    if(position == 0){
      STATE = ERROR;
    }
index2++;
    }

  }
  if(STATE == ERROR){
    printf("ERROR IN FILE CREATION\n");
  }
  else{
 //getFreeFatChain(fp,  fatVar, position, startFAT, int rdCluster, fatSize);
//  printf("\033[32;1m Position: \033[0m%d\n", position);
  getFreeFatChain(fp,  position, fatVar, rootDirecVar, startFAT, position, FatChainSize);

  }
}

void addfile2(FILE *fp, char *str, int position){
int STATE;
int DONE = 1;
char *sibilingFreeStr;
int sibilingFreeNum = -1;

  while(STATE != DONE){
    //printf(" Looking for path \n" );
    if(sibilingFreeNum == 0){
      printf("free path find at position %d\n", position);
      adding_file(fp, position, str);
      addToLinkList(fp, startRootDirectory, position);
      STATE = DONE;
    }
    else{
      sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1);
      sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
      if(sibilingFreeNum == 0){
    //    printf("find free entry \n");
      }
      else{
        position += rootDirecSize;
  //      printf("Incremented\n");
      }
    }
  }

}
/*
This function will deal with the link link that present in the root directory
*/

void addToLinkList(FILE *fp, int startRD, int linkNum){
//printf("From Linked List : %d\n", linkNum );
char* nextLinkstr;
int nextLinkNum = -1;
char buff[20];
char *buff2;
int position = startRD;
int STATE = 1;
int NOTDONE = 2;
int DONE = 3;
int index = 0;
int Link;
int childLink = 1;
int siblingLink =2;

nextLinkstr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
nextLinkNum = (int) strtol(nextLinkstr, (char **)NULL, 16);
if(nextLinkNum == 0){
  Link = childLink;
}
else{
  Link = siblingLink;
  position = nextLinkNum;
}

if(Link == childLink){
  snprintf(buff,sizeof(buff), "%0x", linkNum);
  buff2 = formatString(buff, rootDirecVar.ptrSiblingDirec );
  //printf("Hex value : %s\n", buff2);
  updateVariableRoot(fp, position, rootDirecVar, NULL, NULL, NULL, NULL,
       NULL, NULL, NULL, NULL, NULL, buff2);
}
else{
STATE = NOTDONE;
  while(STATE != DONE ){
  //  printf("Looking for linked list ...\n" );

        if(nextLinkNum == 0){
          snprintf(buff,sizeof(buff), "%0x", linkNum);
          buff2 = formatString(buff, rootDirecVar.ptrSiblingDirec );
        //  printf("Hex value : %s\n", buff2);
          updateVariableRoot(fp, position, rootDirecVar, NULL, NULL, NULL, NULL,
               NULL, NULL, NULL, NULL, buff2, NULL);
          //    printf("%s ",getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1));
          printf("Linked List added! at %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,1,-1) );
          STATE = DONE;
        }
          else{
            index++;
            nextLinkstr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
            nextLinkNum = (int) strtol(nextLinkstr, (char **)NULL, 16);
    //        printf("Searching------------------------------------------------------position: %s sibi: %d\n", nextLinkstr, nextLinkNum  );
            if(nextLinkNum != 0)
            position = nextLinkNum;
          }
  }
}
//  printf("-%s-\n", getRootDirect(fp,startRD, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1) );
}

void adding_folder(FILE *fp, int position, char str[]){
  //printf("Adding folder at %d \n", position);
  char buff[10];
  char *buff2;
  int x = strlen(str);
  snprintf(buff,sizeof(buff), "%0x", x); // converting the int to string to write in file
  buff2 = formatString(buff, rootDirecVar.nameLength ); // ptr to the root directory is formatted
  //printf("FORmatted length ----------------------------------------------------------------------  %s\n", buff2);

  updateVariableRoot(fp, position, rootDirecVar, "1", buff2, str, "1",
     getDateTime(), getDateTime(), NULL, NULL, NULL, NULL);
//printf("Name of folder ~~~~~~: %s",getRootDirect(fp, position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
}

void adding_file(FILE *fp, int position, char str[]){
printf("from 'adding_file' Adding file at %d \n", position);
char buff[10];
char *buff2;
int x = strlen(str);
snprintf(buff,sizeof(buff), "%0x", x); // converting the int to string to write in file
buff2 = formatString(buff, rootDirecVar.nameLength ); // ptr to the root directory is formatted
//printf("FORmatted length ----------------------------------------------------------------------  %s\n", buff2);

updateVariableRoot(fp, position, rootDirecVar, "1", buff2, str, "0",
     getDateTime(), getDateTime(), NULL, NULL, NULL, NULL);
//printf("checking Name of added file --------------------  %s\n",getRootDirect(fp, position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
}

char* selectOption(char buff[]){
  int i = 0;
do{
  if(i > 0){
    printf("Error in the command. Re-select the choice\n" );
  }
  printf("Select a choice from the following [a,b,c,d,e,f,g,h]\n");
  printf("a) Create a file\n");
  printf("b) Create a directory\n");
  printf("c) Open a file\n");
  printf("d) Open a directory\n");
  printf("e) List the files\n");
  printf("f) Delete File\n" );
  printf("g) Delete Directory\n");
  printf("h) Get File Info\n" );
  printf("Enter: ");
  scanf("%s",buff);
  i++;
}while( strcasecmp(buff, "e")!= 0 && strcasecmp(buff,"g") && strcasecmp(buff,"a") != 0 && strcasecmp(buff,"g")==0 && strcasecmp(buff,"b") != 0 && strcasecmp(buff,"c") != 0 && strcasecmp(buff,"d") != 0 && strcasecmp(buff,"f") != 0);

return buff;
}


void initiateRootDirect(FILE *fp, int startRootDirectory){
int rootPosition =  startRootDirectory;
fileWriter2(fp, rootPosition, "1");
rootPosition+= rootDirecVar.validity;
fileWriter2(fp, rootPosition, "01");
rootPosition+= rootDirecVar.nameLength;
fileWriter2(fp, rootPosition, "/");
rootPosition+= rootDirecVar.fileName;
fileWriter2(fp, rootPosition, "1");
}

//94 bytes percluster
void createRootDirectory(FILE *fp, int clusterNum){
    char validity[] = "0"; // 0 is unused , 1 means used
    char nameLength[] = "00";
    char fileName[] = "0000000000000000";
    char filetype[] = "0"; //0 means file , 1 means directory
    char createdDATE[] = "1234567890123456789012345";
    char modifiedDATE[] = "1234567890123456789012345";
    char fileSize[] = "000000";
    char startFatChainBytes[] ="000000";
    char ptrSiblingDirec[] = "000000";
    char ptrChild[] = "000000";
    fileWriter(fp, validity);
    fileWriter(fp, nameLength);
    fileWriter(fp, fileName);
    fileWriter(fp, filetype);
    fileWriter(fp, createdDATE);
    fileWriter(fp, modifiedDATE);
    fileWriter(fp, fileSize);
    fileWriter(fp, startFatChainBytes);
    fileWriter(fp,ptrSiblingDirec);
    fileWriter(fp, ptrChild);
// printRootDirect(fp,position, rootStruct);
//int xy = startRootDirectory + ((clusterNum+1) * 94);
//printf("current: %d ----------------------------  %d \n", Reservedposition, xy);
}

//1024 byte per cluster
void createData(FILE *fp, int clusterNum){
char buff[1024];
int dataPosition = startFAT + (totalFatChain * FatChainSize);
char userData[1024];
fseek(fp, Reservedposition , SEEK_SET);
fwrite(userData, sizeof(char), sizeof(userData), fp);
Reservedposition = Reservedposition + sizeof(userData);
//int xy = startData + ((clusterNum +1) * dataSize);
//printf("Data %d ---- should be %d \n", Reservedposition, xy );
//printf("Positon of DATA: %d\n", Reservedposition );
}


// 7 bytes per cluster
void creatingFat(FILE *fp, int clusterNum){
//printf("position: %d\n", Reservedposition);
  char valid[] = "0"; //If cluster is used = 1 & non-used = 0
  char fatIndex[] ="000";
  char pointerDataBytes[] = "000"; // pointer to the data cluster in bytes

fileWriter(fp,  valid);
fileWriter(fp, fatIndex);
fileWriter(fp,  pointerDataBytes);
//Reservedposition = Reservedposition + FatChainSize;

int xy = 512+ ((clusterNum+1) * 7);
//printf("******** Reserved Position: %d should be : %d\n", Reservedposition, xy);
}



//using 512 bytes
void createReservedSector(FILE *fp){
setValuesReservedSector();
char sectorPerCluster[] = "2"; //Sector per cluster
char sectorForFat[] = "32"; //sector for Fat table in hex (50 sectors)
char  sectorForRD[] = "7DO"; //
char numFat[] = "1";
char fileSystemType[] = "JacobFS";
fileWriter(fp, sectorPerCluster);
fileWriter(fp, sectorForFat);
fileWriter(fp, sectorForRD);
fileWriter(fp,numFat);
fileWriter(fp,fileSystemType);
// the begining of FAT table
Reservedposition = 512;
}

//function to write to a file
void fileWriter(FILE *fp, char str[]){
char buff[6];
//printf("From writer : %s\n Position : %d\n", str, Reservedposition);
fseek(fp, Reservedposition , SEEK_SET);
fwrite(str, sizeof(char), strlen(str), fp);
/*  fseek(fp, Reservedposition , SEEK_SET);
  fread(&buff, 1, strlen(str), fp);
  printf("%s\n", buff);
*/
  Reservedposition = Reservedposition + strlen(str);
}
// getting length of the each varible inside the Root Directory
void setValuesReservedSector(){
  rsVar.sectorPerCluster = 1;
  rsVar.sectorForFat = 2;
  rsVar.sectorForRD = 3;
  rsVar.numFat = 1;
  rsVar.fileSystemType = 7;
}

void setFatVlues(){
fatVar.validity =1;
fatVar.fatIndex =3;
fatVar.dataSize = 3;
}

void setRootDirectVarLen(){
  rootDirecVar.validity = 1;
  rootDirecVar.nameLength = 2;
  rootDirecVar.fileName = 16;
  rootDirecVar.filetype = 1;
  rootDirecVar.createdDate = 25;
  rootDirecVar.modifiedDate =25;
  rootDirecVar.fileSize =6;
  rootDirecVar.startFatChainBytes = 6;
  rootDirecVar.ptrSiblingDirec = 6;
  rootDirecVar.ptrChild = 6;
}


//Fat chain location in bytes
int getFCByteLocation(int index){
int x = (totalReservedSector * bytespSector) + (index * FatChainSize);
//printf("Fat chain bytes: %d\n",x );
return x ;
}
//Location of data cluster in bytes
int getDataByteLocation(int index){
int x= (totalReservedSector * 512) + (totalFatSector * 512) + (index * dataSize);

return x;
}

//This funtion will print the info on the screen
int infoPrinter(FILE *fp, int seekPoint, int len){
  char buff[len];
  fseek(fp,seekPoint,SEEK_SET);
  fread(buff, sizeof(char), len, fp);
  buff[len] = '\0';
  int x = (int) strtol(buff, (char **)NULL, 16);
  return x ;
}

void fileWriter2(FILE *fp, int seekpoint, char str[]){
  fseek(fp, seekpoint , SEEK_SET);
  fwrite(str, sizeof(char), strlen(str), fp);
}


void writeFromFile(FILE *fp, int position, int currentfileSize, int dataIndex){
printf("Data Index ~~~~~~~~~~~~~~~~~~~~ %d\n", dataIndex);
char* getContent = malloc(1024+1);
//char getContent[1024];
char buff3[20];
char *buff2;
int sibilingFreeNum;
char *sibilingFreeStr;
int contentSize;
int fileSize;
int index = dataIndex;
int dataInCluster;
int fileWritePoint;
int dataBytePosition = getDataByteLocation(dataIndex);
int fatFileBytePosition = getFCByteLocation(dataIndex);
int pointer = -1;
int lastposition = fatFileBytePosition;
//printf("Size of : %d Size : %d\n", sizeof(getContent), strlen(getContent) );

printf("\033[33;1mFile Name %s : Size: %d bytes.\033[0m\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), currentfileSize);
printf("Maximum data you can enter at one time is 1024 bytes.\n");
printf("If your data is more than that call write funtion couple of times\n");
printf("Enter the data: \n");
fgets(getContent, 1024, stdin);
scanf(" %[^\n]%*c",getContent);
//scanf("%[^\n]", getContent);
//printf("Size of : %d Size : %d\n", sizeof(getContent), strlen(getContent) );
contentSize = strlen(getContent);

if(contentSize < dataSize){
  while(pointer != 0){
  //  printf("i AM SCREWING YOU codes \n" );
    pointer = getFatValues(fp, lastposition, fatVar,  -1,1, -1);
    if(pointer != 0)
        {
          index = pointer;
          lastposition =  getFCByteLocation(pointer); // in bytes
        }
  }
//printf(" Last fat table of our data:  %d\n", lastposition);

    dataInCluster = getFatValues(fp, lastposition, fatVar,  -1,-1, 1);
    pointer = getFatValues(fp, lastposition, fatVar,  -1,1,-1);
    if(pointer != 0){
      printf("Error in pointer calculation\n");
    }

    if((dataInCluster+contentSize) < 1024 && pointer == 0){
  //printf(" fat table Number: %d\n", index );
          dataBytePosition = getDataByteLocation(index);
          fatFileBytePosition = getFCByteLocation(index);
          fileWritePoint = dataBytePosition + dataInCluster;
          dataInCluster+=contentSize;
          //updating fat table
          snprintf(buff,sizeof(buff), "%0x", dataInCluster);
          buff2 = formatString(buff, fatVar.dataSize);
          updateFatVariable(fp, fatFileBytePosition, fatVar, NULL, NULL, buff2);
          fileWriter2(fp, fileWritePoint, getContent); // updating the content
            //upating the root directory
          fileSize = contentSize + currentfileSize;
          snprintf(buff3,sizeof(buff3), "%0x", fileSize);
          buff2 = formatString(buff3, rootDirecVar.fileSize);
    //      printf("New file Size: %s\n",buff2 );
          updateVariableRoot(fp, position, rootDirecVar, NULL, NULL, NULL, NULL,
                 NULL, getDateTime(), buff2, NULL, NULL, NULL);

        //  fseek(fp,dataBytePosition,SEEK_SET);
          //fread(buff, sizeof(char), fileSize, fp);
      //    printf("Reading from file: %s\n", buff );
  }
    else{

          int x = getFreeFatChain(fp,-1, fatVar, rootDirecVar, startFAT, -1, FatChainSize);
        //  printf("Last postion: %d Index : %d fat  %d\n", lastposition, index , x);
          dataBytePosition = getDataByteLocation(x);
          fatFileBytePosition = getFCByteLocation(x);

          snprintf(buff3,sizeof(buff3), "%0x", x);
          buff2 = formatString(buff3, fatVar.fatIndex);
          updateFatVariable(fp, lastposition, fatVar, NULL, buff2, NULL ); // update the previous fat

          fileWritePoint = dataBytePosition ;
          //dataInCluster+=contentSize;
          //updating fat table
          snprintf(buff,sizeof(buff), "%0x", contentSize);
          buff2 = formatString(buff, fatVar.dataSize);
          updateFatVariable(fp, fatFileBytePosition, fatVar, NULL, NULL, buff2);//updating data size in fata cahin
          fileWriter2(fp, fileWritePoint, getContent); // updating the content

          fileSize = contentSize + currentfileSize;
          snprintf(buff3,sizeof(buff3), "%0x", fileSize);
          buff2 = formatString(buff3, rootDirecVar.fileSize);
          //printf("New file Size from new created fat 'else': %s\n",buff2 );
          updateVariableRoot(fp, position, rootDirecVar, NULL, NULL, NULL, NULL,
                 NULL, getDateTime(), buff2, NULL, NULL, NULL); // updating file size in RD
        // fseek(fp,dataBytePosition,SEEK_SET);
         //fread(buff, sizeof(char), fileSize, fp);
         //printf("Reading from file: %s\n", buff );

    }
}
else{
  printf("You data is beyound 1020 bytes!!!\nYou are only allow enter 1020 bytes at a time\n");
}
free(getContent);
}

void readfromFile(FILE *fp, int position, int fileSize, int dataIndex){
//printf("Inside Read funtion\n");
  char buff1[1025];
  int nextChild = -1;
  int currentIndex = dataIndex;
  int fatPosition;
  int sizeDataInCluster;
  int dataPosition; // start of the data cluster
  if(fileSize > 0){

  while(nextChild != 0){
  //  printf("Inside the loop-- \n" );
    fatPosition =  getFCByteLocation(currentIndex);
    dataPosition = getDataByteLocation(currentIndex);

    sizeDataInCluster = getFatValues(fp, fatPosition , fatVar,  -1,-1, 1);
    fseek(fp,dataPosition,SEEK_SET);
    fread(buff1, sizeof(char), sizeDataInCluster, fp);
    buff1[sizeDataInCluster] = '\0';
    printf("%s",buff1 );
    nextChild = getFatValues(fp, fatPosition , fatVar,  -1,1, -1);
    currentIndex = nextChild;
  }
}
  else{
    printf("Empty File\n");
  }

}
void getDetailFile(){

}
