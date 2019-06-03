FILE *fileOpen(char *file, char *mode);
void fileClose(FILE *fp);

int readChar(FILE *fp);
char *readLine(FILE *fp, int lenmax = IMAX);
char *neReadLine(FILE *fp);
char *nnReadLine(FILE *fp, char *defaultLine = "");
autoList<char *> *readLines(FILE *fp);
autoList<char *> *readLines_x(FILE *fp);

void writeChar(FILE *fp, int chr);
void writeToken(FILE *fp, char *line);
void writeLine(FILE *fp, char *line);
void writeLine_x(FILE *fp, char *line);

uint64 readUI64(FILE *fp, int width = 8);
uint readUI32(FILE *fp, int width = 4);
void writeUI64(FILE *fp, uint64 value, int width = 8);
void writeUI32(FILE *fp, uint value, int width = 4);
