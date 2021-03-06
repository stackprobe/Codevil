void termination(int errorLevel = 0);

#define errorCase(status) \
	do { \
	if((status)) { \
		error(); \
	} \
	} while(0)

#define error() \
	error2(__FILE__, __LINE__, __FUNCTION__)

void error2(char *file, int lineno, char *function);

FILE *GetLogFp(void);

#if LOG_ENABLED
#define LOG(format, ...) (fprintf(GetLogFp(), format, ## __VA_ARGS__), fflush(GetLogFp()))
#else
#define LOG(format, ...) 1
#endif

#define LOGPOS() \
	LOG("[POS] %s %d %s\n", __FILE__, __LINE__, __FUNCTION__)

int hasArgs(int count);
int argIs(char *spell);
char *getArg(int index);
char *nextArg(void);

int IsWindowActive(void);
__int64 GetCurrTime(void);

void execute(char *command);
void execute_x(char *command);
