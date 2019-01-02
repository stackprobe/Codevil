#include "all.h"

char *xcout(char *format, ...)
{
	char *buffer;
	va_list marker;

	va_start(marker, format);

	for(int size = strlen(format) + 128; ; size *= 2)
	{
		errorCase(IMAX < size);

		buffer = (char *)memAlloc(size + 20);
		int retval = _vsnprintf(buffer, size + 10, format, marker);
		buffer[size + 10] = '\0';

		if(0 <= retval && retval <= size)
			break;

		memFree(buffer);
	}
	va_end(marker);

	return buffer;
}
char *strrm(char *line, size_t extend)
{
	return (char *)memRealloc(line, strlen(line) + 1 + extend);
}
char *strr(char *line)
{
	return strrm(line, 0);
}
char *strx(char *line)
{
	return (char *)memClone(line, strlen(line) + 1);
}
void strz(char *&buffer, char *line)
{
	memFree(buffer);
	buffer = strx(line);
}
void strz_x(char *&buffer, char *line)
{
	memFree(buffer);
	buffer = line;
}
int atoi_x(char *line)
{
	int value = atoi(line);
	memFree(line);
	return value;
}
__int64 atoi64_x(char *line)
{
	__int64 value = _atoi64(line);
	memFree(line);
	return value;
}

char *mbs_strrchr(char *str, int chr)
{
	char *ret = NULL;

	for(char *p = str; *p; p = mbsNext(p))
		if(*p == chr)
			ret = p;

	return ret;
}

static int ReplacedFlag;

void replaceChar(char *str, int srcChr, int destChr) // mbs_
{
	for(char *p = str; *p; p = mbsNext(p))
		if(*p == srcChr)
			*p = destChr;
}
char *replace(char *str, char *srcPtn, char *destPtn) // ret: strr()
{
	autoList<char> *buff = new autoList<char>();
	int srcPtnLen = strlen(srcPtn);
	int destPtnLen = strlen(destPtn);

	errorCase(srcPtnLen < 1);
	ReplacedFlag = 0;

	for(char *p = str; *p; )
	{
		if(!strncmp(p, srcPtn, srcPtnLen))
		{
			buff->AddElements(destPtn, destPtnLen);
			ReplacedFlag = 1;
			p += srcPtnLen;
		}
		else
		{
			buff->AddElement(*p);
			p++;
		}
	}
	memFree(str);

	buff->AddElement('\0');
	char *ret = buff->UnbindBuffer();
	delete buff;
	return ret;
}
char *replaceLoop(char *str, char *srcPtn, char *destPtn, int max) // ret: strr()
{
	for(int c = 0; c < max; c++)
	{
		str = replace(str, srcPtn, destPtn);

		if(!ReplacedFlag)
			break;
	}
	return str;
}

char *combine(char *path1, char *path2)
{
	char *path = xcout("%s\\%s", path1, path2);

	replaceChar(path, '\\', '/');
	path = replaceLoop(path, "//", "/", 10);
	replaceChar(path, '/', '\\');

	return path;
}

char *addLine(char *line, char *addPtn)
{
	line = strrm(line, strlen(addPtn));
	strcat(line, addPtn);
	return line;
}
char *addChar(char *line, int chr)
{
	char chrLine[2];

	chrLine[0] = chr;
	chrLine[1] = '\0';

	return addLine(line, chrLine);
}
char *insertLine(char *line, int index, char *insPtn)
{
	char *trailer;

	errorCase(index < 0 || (int)strlen(line) < index);

	trailer = strx(line + index);

	line = strrm(line, strlen(insPtn));
	strcpy(line + index, insPtn);
	strcat(line, trailer);

	memFree(trailer);
	return line;
}
char *insertChar(char *line, int index, int chr)
{
	char insPtn[2];

	insPtn[0] = chr;
	insPtn[1] = '\0';

	return insertLine(line, index, insPtn);
}
void reverseLine(char *line)
{
	char *l = line;
	char *r = strchr(line, '\0');

	if(l < r)
	{
		r--;

		while(l < r)
		{
			int tmp = *l;

			*l = *r;
			*r = tmp;

			l++;
			r--;
		}
	}
}
char *thousandComma(char *line) // ret: strr(line)
{
	uint index;

	reverseLine(line);

	for(index = 3; index < strlen(line); index += 4)
	{
		line = insertChar(line, index, ',');
	}
	reverseLine(line); // •œŒ³
	return line;
}

static char *TokPtr;
static uchar *TokDelims;

void tokinit(char *str, char *delims)
{
	if(str)
	{
		TokPtr = str;
		memFree(TokDelims);
		TokDelims = NULL;
	}
	if(delims)
	{
		char *p;

		if(*delims)
		{
			if(!TokDelims)
				TokDelims = (uchar *)memAlloc(32);

			memset(TokDelims, 0x00, 32);

			for(p = delims; ; p++)
			{
				uint delim = (uint)*p;

				TokDelims[delim / 8] |= (1 << (delim % 8));

				if(!delim)
					break;
			}
		}
		else
		{
			memFree(TokDelims);
			TokDelims = NULL;
		}
	}
}
char *toknext(char *str, char *delims)
{
	char *ret;

	tokinit(str, delims);

	if(!TokPtr)
		return NULL;

	ret = TokPtr;

	if(TokDelims)
	{
		char *p;
		uint upchr;

		for(p = TokPtr; ; p++)
		{
			upchr = (uint)*p;

			if(TokDelims[upchr / 8] & (1u << (upchr % 8)))
				break;
		}
		if(upchr)
		{
			*p = '\0';
			p++;
		}
		else
			p = NULL;

		TokPtr = p;
	}
	else
		TokPtr = NULL;

	return ret;
}
char *ne_toknext(char *str, char *delims)
{
	char *ret = toknext(str, delims);

	errorCase(!ret);
	return ret;
}
