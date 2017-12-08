#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
struct FatVariables{
  int validity;
  int fatIndex;
  int dataSize;
  };
struct RootDirectVarLen{
  int validity;
  int nameLength;
  int fileName;
  int filetype;
  int createdDate;
  int modifiedDate;
  int fileSize;
  int startFatChainBytes;
  int ptrSiblingDirec;
  int ptrChild;
};
extern volatile struct RootDirectVarLen rootDirecVar;
extern volatile struct FatVariables fatVar;
void folderDeleteNormalFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag);
void folderDeleteLastFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag);
void deleteFolder3(FILE *fp, int position);
void getDetails(FILE *fp, int parentPosition);
void readfromFile(FILE *fp, int position, int fileSize, int dataIndex);
void deleteFolder(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar);
void deleteNormalFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag);
void deleteLastFile(FILE *fp, int previousIndex, int currentIndex , int nextIndex, int folderFlag);
void deleteFile(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar);
void deleteFile(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar);
void writeFromFile(FILE *fp,int position, int fileSize, int dataByte);
void updateFatVariable(FILE *fp, int seek, struct FatVariables fatVar, char validity[], char fatIndex[], char pointerToData[]);
int getFCByteLocation(int index);
int getDataByteLocation(int index);
void setFatVlues();
int getFreeFatChain(FILE *fp, int rdPosition, struct FatVariables fatVar, struct RootDirectVarLen rootDirecVar,int startFat,  int rdCluster, int fatSize);
int getFatValues(FILE *fp, int position, struct FatVariables fatVar, int validity, int fatIndex, int pointerToData);
void findFreePath2(FILE *fp, int startRootDirectory, char** path, int length, int rootDirecSize, int folderNum);
void openFolder1(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar);
void openFile(FILE *fp, char** path, int currentPosition, struct RootDirectVarLen rootDirecVar);
int findFreePath(FILE *fp, int startRootDirectory, char** path, int length, int rootDirecSize, int folderNum);
void adding_folder(FILE *fp, int position, char str[]);
void openFolder(FILE *fp , int position);
void getList(FILE *fp, int startRD);
void addfile2(FILE *fp, char *str, int position);
int addfileAndFolder(FILE *fp, char** path, int fileType);
int addFolder(FILE *fp, char** path);
char* getDateTime();
void updateVariableRoot(FILE *fp, int seek,  struct RootDirectVarLen rootStruct, char validity[], char nameLen[], char name[], char fileType[],
   char cDate[], char mDate[], char fileSize[], char startFatClus[],char ptrNextClust[],char ptrChild[]);
char** makelist(char *str);
void addToLinkList(FILE *fp, int startRD, int linkNum);
char* formatString(char str[], int intentLen);
void adding_file(FILE *fp, int position, char *str);
int getTotalWord(char str[]);
char** makelist(char *str);
int getTotalWord(char *buff);
char* selectOption(char buff[]);
void fileWriter2(FILE *fp, int seekpoint, char str[]);
void fileWriter(FILE *fp, char str[]);
void setValuesReservedSector();
void setRootDirectVarLen();
void createReservedSector(FILE *fp);
int infoPrinter(FILE *fp, int seekPoint, int len);
void creatingFat(FILE *fp, int clusterNum);
void createData(FILE *fp, int clusterNum);
void createRootDirectory(FILE *fp, int clusterNum);
char* getRootDirect(FILE *fp, int position, struct RootDirectVarLen rootDirecVar, int validity, int nameLen, int name, int fileType, int cDate,
  int mDate, int fsize, int startClusterFatBytes, int ptrRD, int ptrRDChild);
char* getString(FILE *fp, int seek, int stringlen);
void initiateRootDirect(FILE *fp, int startRootDirectory);
void getPath(FILE *fp, char buff[], char** args, char *str);
