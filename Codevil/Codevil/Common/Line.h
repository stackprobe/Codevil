#define m_isEmpty(line) \
	(!(line) || !*(line))

#define isMbc1(c) ( \
	'\x81' <= (c) && (c) <= '\x9f' || \
	'\xe0' <= (c) && (c) <= '\xfc')

#define isMbc(p) \
	(isMbc1((p)[0]) && (p)[1])
//	(_ismbblead((p)[0]) && (p)[1])
//	(_ismbblead((p)[0]) && _ismbbtrail((p)[1]))

#define mbsNext(p) \
	(p + (isMbc(p) ? 2 : 1))

char *xcout(char *format, ...);
char *strrm(char *line, size_t extend);
char *strr(char *line);
char *strx(char *line);
void strz(char *&buffer, char *line);
void strz_x(char *&buffer, char *line);
int atoi_x(char *line);
__int64 atoi64_x(char *line);

char *mbs_strrchr(char *str, int chr);

void replaceChar(char *str, int srcChr, int destChr);
char *replaceLine(char *str, char *srcPtn, char *destPtn, int ignoreCase = 0);
char *replaceLineLoop(char *str, char *srcPtn, char *destPtn, int ignoreCase = 0, int loopMax = 20);

char *combine(char *path1, char *path2);

char *addLine(char *line, char *addPtn);
char *addChar(char *line, int chr);
char *insertLine(char *line, int index, char *insPtn);
char *insertChar(char *line, int index, int chr);
void reverseLine(char *line);
char *thousandComma(char *line);

void tokinit(char *str, char *delims);
char *toknext(char *str, char *delims);
char *ne_toknext(char *str, char *delims);
