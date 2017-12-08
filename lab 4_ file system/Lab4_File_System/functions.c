  #include "lab4.h"

  void getDetails(FILE *fp, int parentPosition){
  printf("********************Information of Files and Folders***********************\n");
    char* clusterString ;
    int clusterNum;
    int position = parentPosition;
    int STATE ;
    int DONE = 1 ;
    int NOTDONE = 2;
    STATE = NOTDONE;
    int node;
    int parent = 1;
    int child =2;
    node = parent;
    int i = 0;
    while(STATE != DONE ){
      //printf("Inside\n" );
      if(node == parent){
       clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
       printf("\033[32;1m '%s'\033[0m  <- Parent Directory\n", clusterString);
       clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
       clusterNum = (int) strtol(clusterString, (char **)NULL, 16);
      // printf("----------------------------------------------cluser number: %s\n", str2);
       position = clusterNum;
       node = child;
          if(position == 0){
            STATE = DONE;
          }
        }
      else{
        clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
        if(strcasecmp(clusterString,"1") == 0){
          clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
          printf("\033[32;1mDirectory Name: %s \033[0m\n", clusterString );
          printf("Created Date  : %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,1,-1,-1,-1,-1,-1));
        }
        else{
        clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
        printf("File Name: %s\nCreated Date  : %sModified Date : %sSize          : %s bytes\n",clusterString, getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,1,-1,-1,-1,-1,-1), getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,1,-1,-1,-1,-1), getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,1,-1,-1,-1));
        }
        clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        clusterNum = (int) strtol(clusterString, (char **)NULL, 16);
        position = clusterNum;
      //  printf("Next  position %d \n",position);

            if(position == 0) {
              STATE = DONE;
            }
      }
      i++;
    }
  printf("----------------------------------------------------------------------\n");
  }


void getList(FILE *fp, int parentPosition){
printf("**********************Files and Folders*****************************\n");
  char* clusterString ;
  int clusterNum;
  int position = parentPosition;
  int STATE ;
  int DONE = 1 ;
  int NOTDONE = 2;
  STATE = NOTDONE;
  int node;
  int parent = 1;
  int child =2;
  node = parent;
  int i = 0;
  while(STATE != DONE ){
    //printf("Inside\n" );
    if(node == parent){
     clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
     printf("\033[32;1m%d) '%s'\033[0m  <- Parent Directory\n", i, clusterString);
     clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
     clusterNum = (int) strtol(clusterString, (char **)NULL, 16);
    // printf("----------------------------------------------cluser number: %s\n", str2);
     position = clusterNum;
     node = child;
        if(position == 0){
          STATE = DONE;
        }
      }
    else{
      clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
      if(strcasecmp(clusterString,"1") == 0){
        clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
        printf("\033[32;1m___________%d) %s \033[0m\n",i, clusterString );
      }
      else{
      clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
      printf("___________%d) %s\n",i, clusterString);
      }
      clusterString =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
      clusterNum = (int) strtol(clusterString, (char **)NULL, 16);
      position = clusterNum;
    //  printf("Next  position %d \n",position);

          if(position == 0) {
            STATE = DONE;
          }
    }
    i++;
  }
printf("----------------------------------------------------------------------\n");
}


/*
void getList(FILE *fp, int startRD){
//printing the parent folder Name
char* name;
char* str1;
int nextFileNum ;
int position = startRD;
name = getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
printf("%s\n", name);
str1 =getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
nextFileNum = (int) strtol(str1, (char **)NULL, 16);
int STATE ;
int NOTDONE = 1;
int DONE = 2;
STATE = NOTDONE;

  while(STATE != DONE){
    position = nextFileNum;
    name = getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1);
    printf("----  %s\n",name );
    str1 =getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
    nextFileNum = (int) strtol(str1, (char **)NULL, 16);
  }
}
*/

//
void linkList2(FILE *fp, int folderNum, int newLinkNum){
  //printf("RRRRRRRRRRRRRRRRRRRRRRRROOOOOOKS\n");
  char *sibilingFreeStr;
  int sibilingFreeNum ;
  int position = folderNum;
  int Link;
  int childLink =1;
  int sibilingLink = 2;
  char buff[20];
  char *buff2;
  int STATE;
  int DONE =1;
  int NOTDONE =2;
  int RUNNING =3;
  STATE = NOTDONE;

  sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  if(sibilingFreeNum == 0){
//printf("FIRST FILE----------------------------------------------------------------------------------- -'%s'-\n", sibilingFreeStr);
    Link = childLink;
    snprintf(buff,sizeof(buff), "%0x", newLinkNum);
    buff2 = formatString(buff, rootDirecVar.ptrChild);
    updateVariableRoot(fp, position, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, buff2);
  }
  else{
  Link = sibilingLink;
  position = sibilingFreeNum;
  }

  if(Link == sibilingLink){
      while(STATE != DONE){
        //printf("Lonking for new \n");
        sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
        if(sibilingFreeNum == 0){
          STATE = DONE;
        //  printf(" STATE is DOne %d\n",position );
        }
        else{
          position = sibilingFreeNum;
        }
      }
      if(STATE == DONE){
      //  sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        //sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
        snprintf(buff,sizeof(buff), "%0x", newLinkNum);
        buff2 = formatString(buff, rootDirecVar.ptrSiblingDirec);
        updateVariableRoot(fp, position, rootDirecVar, NULL, NULL, NULL, NULL,
             NULL, NULL, NULL, NULL,  buff2, NULL);
      //  printf("Added to List : name  %s currentLink %d nextLink: %s \n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1),position, getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1));
      }

  }

}



// find free path and add the file. Then call the linklist with the root position
int  findFreePath(FILE *fp, int startRootDirectory, char** path, int length, int rootDirecSize, int folderNum){
int STATE ;
int DONE =1;
int NOTDONE =2;
STATE = NOTDONE;
int sibilingFreeNum = -1;
char *sibilingFreeStr;
int position = startRootDirectory;

  while(STATE != DONE){
    //printf(" Looking for path \n" );
    if(sibilingFreeNum == 0){
          STATE = DONE;
          //printf("free path find at position %d\n", position);
          STATE = DONE;
          adding_file(fp, position, path[length-1]);
          linkList2(fp, folderNum, position);

          //addToLinkList(fp, startRootDirectory, position);
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
            }
    }
  }
return position;
}


// find free path and add the file. Then call the linklist with the root position
void findFreePath2(FILE *fp, int startRootDirectory, char** path, int length, int rootDirecSize, int folderNum){
int STATE ;
int DONE =1;
int NOTDONE =2;
STATE = NOTDONE;
int sibilingFreeNum = -1;
char *sibilingFreeStr;
int position = startRootDirectory;

  while(STATE != DONE){
    //printf(" Looking for path \n" );
    if(sibilingFreeNum == 0){
          STATE = DONE;
      //    printf("free path find at position %d\n", position);
          STATE = DONE;
          adding_folder(fp, position, path[length-1]);
          linkList2(fp, folderNum, position);

          //addToLinkList(fp, startRootDirectory, position);
    }
    else{
          sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1);
          sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
          if(sibilingFreeNum == 0){
    //          printf("find free entry \n");
            }
          else{
              position += rootDirecSize;
  //            printf("Incremented\n");
            }
    }
  }

}




void openFile(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar){
//printf("path: %s, current position : %d\n", path[0], currentPosition);
int length =0 ;
while(path[length] != NULL){
  length++;
}

char buff[20];
int index = 0;
int position = currentPosition;
int STATE ;
int RUNNING = 1;
int NOTFOUND = 2;
int NEXT = 3;
int ERROR = 5;
int FOUND = 4;
int PARENTFOUND = 7;
int mode;
int parent =1 ;
int child = 2;
mode = parent;
int sibilingFreeNum;
char *sibilingFreeStr;
char getfuntion[10];
int index2;
int fileSize;
int dataPosition;
if(length == 1){
sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
position = sibilingFreeNum;
STATE = RUNNING;
index = 0;
  while(STATE != FOUND && STATE != ERROR){
    if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
  //    printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
        if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "0") == 0){
    //      printf("-------------------------------------Layer 3 foldertype matched \n");
          if(path[index+1] == NULL){
            STATE = FOUND;
            printf("'From file Open'- File FOund at %d\n", position);
          }
        }
      }

      if(STATE != FOUND && STATE != ERROR){
        sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
        position = sibilingFreeNum;
      }
      if(STATE != FOUND && position == 0){
        STATE = ERROR;
      }
  }
}

else{

while(STATE != PARENTFOUND && STATE != ERROR){
  if(mode == parent ){
    //printf("Openfile: Serching ...\n");
    //printf("Name current folder from open : %s next number: %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1), getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1));
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    mode = child;
    position = sibilingFreeNum;
  }
  else{
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    position = sibilingFreeNum;
  }
  if(position == 0)
  {
    STATE = ERROR;
  }
  if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
    //printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1));
      if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "1") == 0){
        //printf("-------------------------------------Layer 3 foldertype matched \n");

        STATE = NEXT;
        index++;
        mode = parent;

        if(path[index+1] == NULL){
          STATE = PARENTFOUND;
        //  printf(" Parent folder found! %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1));
  //      sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    //    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
      //  printf("Next file entry Number: %d\n", sibilingFreeNum );


        }
      }
    }
}
}

if(STATE == PARENTFOUND){
  sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  position = sibilingFreeNum;
  STATE = RUNNING;
  index = length -1;
  while(STATE != FOUND && STATE != ERROR){

    if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
      //printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
        if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "0") == 0){
    //      printf("-------------------------------------Layer 3 foldertype matched \n");
          if(path[index+1] == NULL){
            STATE = FOUND;
            printf("'From file Open'- File FOund \n");
          }
        }
      }

      if(STATE != FOUND && STATE != ERROR){
        sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
        position = sibilingFreeNum;
      }
      if(STATE != FOUND && position == 0){
        STATE = ERROR;
      }
  }


}
if(STATE == FOUND){
index2 = 0;
  do{
    if(index2 == 1){
      printf("Wrong Input! Please Re-enter\n");
      index2 = 0;
    }
    if(index2 == 0){
    printf("\nNow read and write to the file\n");
    printf("Choose the following choices [a,b,c]\n");
    printf("a) Write to file\n");
    printf("b) Read from file\n");
    printf("c) close the file\n");
    scanf("%s", getfuntion);
    index2 = 0;
    }
    if(strcasecmp(getfuntion, "a") == 0 )
    {
    //  printf("File Launched ! %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,1,-1,-1,-1);
    fileSize = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
    dataPosition = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  //  printf("Position %d retrived fat value  %d in str: %s\n",position, dataPosition, sibilingFreeStr);

    writeFromFile(fp,position, fileSize, dataPosition);
    }
    if(strcasecmp(getfuntion, "b") == 0 ){
      sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,1,-1,-1,-1);
      fileSize = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
      sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
      dataPosition = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    //  printf("retrived fat value  %d in str: %s\n", dataPosition, sibilingFreeStr);
      readfromFile(fp,position, fileSize, dataPosition);
    }
    if(strcasecmp(getfuntion, "c") == 0 )
    {
      break;
    }
    if(strcasecmp(getfuntion, "a") != 0 && strcasecmp(getfuntion, "b") != 0 && strcasecmp(getfuntion, "c") != 0){
      index2++;
    }
}while(strcasecmp(getfuntion, "c") != 0 );

}

if(STATE == ERROR){
  printf("No Matching file found\n");
}

}


void openFolder1(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar){
int length = 0 ;
while(path[length] != NULL){
  length++;
}
char buff[20];
char secondbuff[100];
int index = 0;
int position = currentPosition;
int STATE ;
int RUNNING = 1;
int NOTFOUND = 2;
int NEXT = 3;
int ERROR = 5;
int FOUND = 4;
int mode;
int parent =1 ;
int child = 2;
mode = parent;
int sibilingFreeNum;
char *sibilingFreeStr;
while(STATE != FOUND && STATE != ERROR){
  if(mode == parent ){
    //printf("Open: Serching ...\n");
  //  printf("Name current folder from open : %s next number: %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1), getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1));
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    mode = child;
    position = sibilingFreeNum;
  }
  else{
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    position = sibilingFreeNum;
  }
  if(position == 0)
  {
    STATE = ERROR;
  }
  if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
    //printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1));
      if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "1") == 0){
    //    printf("-------------------------------------Layer 3 foldertype matched \n");

        STATE = NEXT;
        index++;
        mode = parent;

        if(path[index] == NULL){
          STATE = FOUND;
          printf("folder found!\n");
        sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
        sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  //      printf("Next file entry Number: %d\n", sibilingFreeNum );
        do{
            printf("Choose from the following [a,b,c,d, quit]\n");
            printf("a) Open file\n" );
            printf("b) Open Directory\n");
            printf("c) Get files Info\n" );
            printf("d) To get the List of files and folders \n");
            printf("Enter 'quit' to close folder\n");
            printf("Enter:\n" );
            scanf("%s", buff);

            if(strcasecmp(buff, "d") == 0)
              {
                getList(fp, position);
              }

              else if(strcasecmp(buff,"c") == 0){
                 getDetails(fp, position);
              }
              else if(strcasecmp(buff,"a") == 0){
                printf("Enter the full path from root: \n");
                scanf("%s", secondbuff);
                char** args = makelist(secondbuff);
                openFile(fp, args, currentPosition, rootDirecVar);
              }
              else if(strcasecmp(buff,"b") == 0){
                printf("Enter the full path from root: \n");
                scanf("%s", secondbuff);
                char** args = makelist(secondbuff);
                openFolder1(fp, args, currentPosition, rootDirecVar);
              }
        }while(strcasecmp(buff, "quit") != 0);

        }
      }
    }
}

if(STATE == ERROR){
  printf("No Matching Folder found\n");
}
}
//-----------------------------------------------------------------------------

void deleteFile(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar){
//printf("path: %s, current position : %d\n", path[0], currentPosition);
int length =0 ;

while(path[length] != NULL){
  length++;
}
int folderFlag = 0;
int previousIndex= currentPosition;
int currentIndex = -1;
int nextIndex = -1;
char buff[20];
int index = 0;
int position = currentPosition;
int STATE ;
int RUNNING = 1;
int NOTFOUND = 2;
int NEXT = 3;
int ERROR = 5;
int FOUND = 4;
int PARENTFOUND = 7;
int mode;
int parent =1 ;
int child = 2;
mode = parent;
int sibilingFreeNum;
char *sibilingFreeStr;
char getfuntion[10];
int index2;
int fileSize;
int dataPosition;

if(length == 1){

    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    position = sibilingFreeNum;
    STATE = RUNNING;
    index = 0;

        while(STATE != FOUND && STATE != ERROR){
          currentIndex = sibilingFreeNum;
            if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
          //    printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
                if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "0") == 0){
            //      printf("-------------------------------------Layer 3 foldertype matched \n");
                  if(path[index+1] == NULL){
                    STATE = FOUND;
                    printf("'From file Open'- File FOund at %d\n", position);
                    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
                    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
                    if(sibilingFreeNum != 0){
                      nextIndex = sibilingFreeNum;
                    }
                  }
                }
              }

              if(STATE != FOUND && STATE != ERROR){
                sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
                sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
                position = sibilingFreeNum;
                previousIndex = currentIndex;
                currentIndex = sibilingFreeNum;
                folderFlag++;
              }
              if(STATE != FOUND && position == 0){
                STATE = ERROR;
              }
        }
}

else{

while(STATE != PARENTFOUND && STATE != ERROR){
  if(mode == parent ){
    //printf("Openfile: Serching ...\n");
    //printf("Name current folder from open : %s next number: %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1), getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1));
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    mode = child;
    position = sibilingFreeNum;
  }
  else{
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    position = sibilingFreeNum;
  }
  if(position == 0)
  {
    STATE = ERROR;
  }
  if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
    //printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1));
      if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "1") == 0){
      //  printf("-------------------------------------Layer 3 foldertype matched \n");

        STATE = NEXT;
        index++;
        mode = parent;

        if(path[index+1] == NULL){
          STATE = PARENTFOUND;
      //    printf(" Parent folder found! %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1));

        }
      }
    }
}
}

if(STATE == PARENTFOUND){
  previousIndex = position;
  sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  position = sibilingFreeNum;
  STATE = RUNNING;
  index = length -1;
  while(STATE != FOUND && STATE != ERROR){
    currentIndex = sibilingFreeNum;

    if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
    //  printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1));
        if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "0") == 0){
  //        printf("-------------------------------------Layer 3 foldertype matched \n");
          if(path[index+1] == NULL){
            STATE = FOUND;
            printf("'From file Open'- File FOund at %d\n", position);
            sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
            sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
            if(sibilingFreeNum != 0){
              nextIndex = sibilingFreeNum;
            }
          }
        }
      }

      if(STATE != FOUND && STATE != ERROR){
        sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
        sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
        position = sibilingFreeNum;
        previousIndex = currentIndex;
        currentIndex = sibilingFreeNum;
        folderFlag++;
      }
      if(STATE != FOUND && position == 0){
        STATE = ERROR;
      }
  }


}
if(STATE == FOUND){
//printf("Previous Index %d current Index %d Next Index %d \n", previousIndex, currentIndex, nextIndex);
    if(nextIndex == -1){
        deleteLastFile(fp, previousIndex, currentIndex ,  nextIndex, folderFlag);
    }
    else{
       deleteNormalFile(fp, previousIndex, currentIndex , nextIndex, folderFlag);
      }

}
if(STATE == ERROR){
  printf("No Matching file found\n");
}
}

void deleteLastFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag){
  int sibilingFreeNum;
  char *sibilingFreeStr;
  int fatNum;
  int fatNumBytes;
  char *fatStr;
  sibilingFreeStr = getRootDirect(fp,previousIndex, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  fatStr = getRootDirect(fp,currentIndex, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
  fatNum = (int) strtol(fatStr, (char **)NULL, 16);
//  printf("Retrived Fat Index was--------------------------------------------- %d\n", fatNum );
  fatNumBytes = getFCByteLocation(fatNum);
  if(sibilingFreeNum == 1 && folderFlag == 0){
    //printf("My previous link is a directory \n");
    //updating the previous link
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, "000000");
   // removing the current link
    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
          NULL, NULL, NULL, "000000", "000000", "000000");
   //removing the fat
   updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");

  }
  else{
    //printf("My previous link is a file\n" );
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, "000000", NULL);
    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
         NULL, NULL, NULL, "000000", "000000", "000000");
    // updating the fat
    updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");
  }

}

void deleteNormalFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag){
  int sibilingFreeNum;
  char *sibilingFreeStr;
  int fatNum;
  int fatNumBytes;
  char *fatStr;
  char buff[10];
  char *nextStr;
  snprintf(buff,sizeof(buff), "%0x", nextIndex);
  nextStr = formatString(buff, rootDirecVar.startFatChainBytes);

  sibilingFreeStr = getRootDirect(fp,previousIndex, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);

  fatStr = getRootDirect(fp,currentIndex, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
  fatNum = (int) strtol(fatStr, (char **)NULL, 16);
  fatNumBytes = getFCByteLocation(fatNum);

  if(sibilingFreeNum == 1 && folderFlag == 0) {
  //  printf("My previous link is a directory \n");
    //updating the previous link
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, nextStr);
   // removing the current link
    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
          NULL, NULL, NULL, "000000", "000000", "000000");
   //removing the fat
   updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");

  }
  else{
  //  printf("My previous link is a file\n" );
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, nextStr, NULL);

    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
         NULL, NULL, NULL, "000000", "000000", "000000");
    // updating the fat
    updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");
  }

}


void folderDeleteLastFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag){
  int sibilingFreeNum;
  char *sibilingFreeStr;
  //int fatNum;
  //int fatNumBytes;
  //char *fatStr;
  sibilingFreeStr = getRootDirect(fp,previousIndex, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
/*  fatStr = getRootDirect(fp,currentIndex, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
  fatNum = (int) strtol(fatStr, (char **)NULL, 16);
*///  printf("Retrived Fat Index was--------------------------------------------- %d\n", fatNum );
  //fatNumBytes = getFCByteLocation(fatNum);
  if(sibilingFreeNum == 1 && folderFlag == 0){
    //printf("My previous link is a directory \n");
    //updating the previous link
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, "000000");
   // removing the current link
    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
          NULL, NULL, NULL, "000000", "000000", "000000");
   //removing the fat
   //updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");

  }
  else{
  //  printf("My previous link is a file\n" );
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, "000000", NULL);
    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
         NULL, NULL, NULL, "000000", "000000", "000000");
    // updating the fat
    //updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");
  }

}

void folderDeleteNormalFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag){
  int sibilingFreeNum;
  char *sibilingFreeStr;
  //int fatNum;
//  int fatNumBytes;
//  char *fatStr;
  char buff[10];
  char *nextStr;
  snprintf(buff,sizeof(buff), "%0x", nextIndex);
  nextStr = formatString(buff, rootDirecVar.startFatChainBytes);

  sibilingFreeStr = getRootDirect(fp,previousIndex, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);

  /*fatStr = getRootDirect(fp,currentIndex, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
  fatNum = (int) strtol(fatStr, (char **)NULL, 16);
  fatNumBytes = getFCByteLocation(fatNum);
*/
  if(sibilingFreeNum == 1 && folderFlag == 0) {
  //  printf("My previous link is a directory \n");
    //updating the previous link
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, NULL, nextStr);
   // removing the current link
    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
          NULL, NULL, NULL, "000000", "000000", "000000");
   //removing the fat
  // updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");

  }
  else{
//    printf("My previous link is a file\n" );
    updateVariableRoot(fp, previousIndex, rootDirecVar, NULL, NULL, NULL, NULL,
         NULL, NULL, NULL, NULL, nextStr, NULL);

    updateVariableRoot(fp, currentIndex, rootDirecVar, "0", NULL, NULL, NULL,
         NULL, NULL, NULL, "000000", "000000", "000000");
    // updating the fat
    //updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");
  }

}




void deleteFolder(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar){
int length = 0 ;
while(path[length] != NULL){
  length++;
}
int previousIndex= currentPosition;
int currentIndex = -1;
int nextIndex = -1;
int folderFlag = 0;
int flagturn = 0;
char buff[20];
char secondbuff[100];
int index = 0;
int position = currentPosition;
int STATE ;
int RUNNING = 1;
int NOTFOUND = 2;
int NEXT = 3;
int ERROR = 5;
int FOUND = 4;
int mode;
int parent =1 ;
int child = 2;
mode = parent;
int sibilingFreeNum;
char *sibilingFreeStr;
while(STATE != FOUND && STATE != ERROR){

  if(mode == parent && index == (length-1)){
    flagturn = 1;
  }

  if(mode == parent ){
    //printf("Open: Serching ...\n");
    //printf("Name current folder from open : %s next number: %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1), getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1));
    previousIndex = position;
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    mode = child;
    position = sibilingFreeNum;
    currentIndex = sibilingFreeNum;
  }

  else{
    sibilingFreeStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
    sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    position = sibilingFreeNum;
    previousIndex = currentIndex;
    currentIndex = sibilingFreeNum;
    if(flagturn == 1){
      folderFlag++;
    }
  }
  if(position == 0)
  {
    STATE = ERROR;
  }
  if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,-1), path[index]) == 0 ){
    //printf("-------------------------------------Layer 2 name matched %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1));
      if(strcmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,-1), "1") == 0){
      //  printf("-------------------------------------Layer 3 foldertype matched \n");

        STATE = NEXT;
        index++;
        mode = parent;

        if(path[index] == NULL){
          STATE = FOUND;
          printf("folder found!\n");
          sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
          sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
    //      printf("Next file entry Number: %d\n", sibilingFreeNum );
          if(sibilingFreeNum != 0){
            nextIndex = sibilingFreeNum;
          }

        }
      }
    }
}

if(STATE == ERROR){
  printf("No Matching Folder found\n");
}
else{
  if(nextIndex == -1){
  //  printf("Last file ! Prev %d curr: %d next %d  flag: %d\n", previousIndex, currentIndex, nextIndex, folderFlag);
  sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  if(sibilingFreeNum != 0){
    deleteFolder3(fp, sibilingFreeNum);
  }
 folderDeleteLastFile(fp, previousIndex, currentIndex ,  nextIndex, folderFlag);

  }
  else{
  //  printf("Middle file ! Prev %d curr: %d next %d flag %d\n", previousIndex, currentIndex,nextIndex, folderFlag);
  sibilingFreeStr =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  sibilingFreeNum = (int) strtol(sibilingFreeStr, (char **)NULL, 16);
  if(sibilingFreeNum != 0){
    deleteFolder3(fp, sibilingFreeNum);
  }
  folderDeleteNormalFile(fp, previousIndex, currentIndex , nextIndex, folderFlag);

    }

}
}

void deleteFolder3(FILE *fp, int position){

  int fatNum;
  int fatNumBytes;
  char *fatStr;
  char *validstr;
  int position1 , position2;
  char* childString  =  getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  int childNum = (int) strtol(childString, (char **)NULL, 16);
  char* siblingString  = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
  int siblingNum = (int) strtol(siblingString, (char **)NULL, 16);
  position1 = childNum;
  position2 = siblingNum;
  while(childNum != 0 || siblingNum != 0){
    if(childNum != 0){
      deleteFolder3(fp, position1);
    }
    if(siblingNum != 0){
      deleteFolder3(fp, position2);
    }
     childString  =  getRootDirect(fp,childNum, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,-1,1);
     childNum = (int) strtol(childString, (char **)NULL, 16);
     siblingString  = getRootDirect(fp,siblingNum, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,-1,1,-1);
     siblingNum = (int) strtol(siblingString, (char **)NULL, 16);
    position1 = childNum;
    position2 = siblingNum;
  }
       validstr = getRootDirect(fp,position, rootDirecVar, 1,-1,-1,-1,-1,-1,-1,-1,-1,1);
  if(strcasecmp(validstr,"1") == 0){
      printf(" ~~~~ %s\n", getRootDirect(fp,position, rootDirecVar, -1,-1,1,-1,-1,-1,-1,-1,-1,1));
      if(strcasecmp(getRootDirect(fp,position, rootDirecVar, -1,-1,-1,1,-1,-1,-1,-1,-1,1),"0") == 0){
          fatStr = getRootDirect(fp,position, rootDirecVar, -1,-1,-1,-1,-1,-1,-1,1,-1,-1);
          fatNum = (int) strtol(fatStr, (char **)NULL, 16);
          fatNumBytes = getFCByteLocation(fatNum);
          printf("Upadting Fat : %d\n", fatNum);
          updateFatVariable(fp, fatNumBytes, fatVar, "0", "000", "000");
      }
      printf("Updating Root Direc %d\n", position );
      updateVariableRoot(fp, position, rootDirecVar, "0", NULL, NULL, NULL,
         NULL, NULL, NULL, "000000", "000000", "000000");
  }
}
