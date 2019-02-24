FILE *fileOpen(char *file, char *mode);
void fileClose(FILE *fp);

autoList<uchar> *readAllBytes(char *file);
autoList<uchar> *readAllBytes_x(char *file);

// FILE ver
int readChar(FILE *fp);
char *readLine(FILE *fp, int lenmax = IMAX);
char *neReadLine(FILE *fp);
char *nnReadLine(FILE *fp, char *defaultLine = "");
autoList<char *> *readLines(FILE *fp);
autoList<char *> *readLines_x(FILE *fp);

// fileData ver
int readChar(autoList<uchar> *fileData, int &rIndex);
char *readLine(autoList<uchar> *fileData, int &rIndex);
char *neReadLine(autoList<uchar> *fileData, int &rIndex);
char *nnReadLine(autoList<uchar> *fileData, int &rIndex, char *defaultLine = "");
autoList<char *> *readLines(autoList<uchar> *fileData);
autoList<char *> *readLines_x(autoList<uchar> *fileData);

void writeAllBytes(char *file, autoList<uchar> *fileData);
void writeAllBytes_cx(char *file, autoList<uchar> *fileData);

// FILE ver
void writeChar(FILE *fp, int chr);
void writeToken(FILE *fp, char *line);
void writeLine(FILE *fp, char *line);
void writeLine_x(FILE *fp, char *line);

// fileData ver
void writeChar(autoList<uchar> *fileData, int chr);
void writeToken(autoList<uchar> *fileData, char *token);
void writeLine(autoList<uchar> *fileData, char *line);
void writeLine_x(autoList<uchar> *fileData, char *line);

// FILE ver
uint64 readUI64(FILE *fp, int width = 8);
uint readUI32(FILE *fp, int width = 4);
void writeUI64(FILE *fp, uint64 value, int width = 8);
void writeUI32(FILE *fp, uint value, int width = 4);

// fileData ver
uint64 readUI64(autoList<uchar> *fileData, int &rIndex, int width = 8);
uint readUI32(autoList<uchar> *fileData, int &rIndex, int width = 4);
void writeUI64(autoList<uchar> *fileData, uint64 value, int width = 8);
void writeUI32(autoList<uchar> *fileData, uint value, int width = 4);

autoList<uchar> *readBlock(FILE *fp, int width);
autoList<uchar> *readBlock(autoList<uchar> *fileData, int &rIndex, int width);
