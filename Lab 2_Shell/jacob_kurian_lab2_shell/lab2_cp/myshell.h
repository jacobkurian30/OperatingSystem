char **getSecondArgument(char **ptr, int start, int final);
char **gettingFirstArgument(char **ptr, int size);
char **getArguments(char *str);
int getTotalNumberArgs(char *str);
void dirCall();
void getEnvironmental();
void changeDirec(char *str);
void screenCleaner();
void echo(char **ptr);
void batchfile(int argc, char *argv[]);
int pipingfuntion(char **prog1, char **prog2);
void  getPathName();
void getFreeMemory(char **ptr, int size);
void inpputer(char **ptr, char **ptr2,  int i);
void outputter(char **ptr, char **ptr2, int i);
int getStringLength(char **ptr);
void inputOutput(char **ptr, char **ptr2,  int i);
void outputterAppend(char **ptr, char **ptr2, int i);
int  builtRedirection(char **ptr);
int helpMaualWithMore();
char **getFirstArg(char **ptr, char c[]);
void getPause();
void print_decendants(char *pathname, int depth);
int is_dir(char *path_name);

//------------------------------------------------

int getlen(char *fileName);
char *getStr(char *fileName);
int getNumberLines(char *str);
char **getDoubleArray(char *str, char *fileName);
char **getBatchFile(int argc, char **argv);
