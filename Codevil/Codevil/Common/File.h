// ---- getFileList ----

extern struct _finddata_t lastFindData;

void getFileList(char *dir, autoList<char *> *subDirs, autoList<char *> *files);
void updateFindData(char *path);

// ----

char *combine(char *path1, char *path2);

int accessible(char *path);
char *refLocalPath(char *path);
void createFile(char *file);
void createDir(char *dir);
void deleteFile(char *file);
void deleteDir(char *dir);

char *getCwd(void);
void changeCwd(char *dir);
void addCwd(char *dir);
void unaddCwd(void);

char *getAppTempDir(void);
char *makeTempPath(char *ext = NULL);
char *makeTempFile(char *ext = NULL);
char *makeTempDir(char *ext = NULL);

__int64 getFileSizeFP(FILE *fp);
__int64 getFileSizeFPSS(FILE *fp);
__int64 getFileSize(char *file);
