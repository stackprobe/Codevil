#include "all.h"

static FILE *Game_rfopen(char *file, char *mode)
{
	FILE *fp;

	for(int c = 0; ; c++)
	{
		fp = fopen(file, mode);

		if(fp || 8 < c)
			break;

		LOGPOS();
		Sleep(100);
	}
	return fp;
}
FILE *fileOpen(char *file, char *mode)
{
	FILE *fp = Game_rfopen(file, mode);

	if(!fp) // ? Ž¸”s
	{
		{
			static int passed;

			if(passed)
				error();

			passed = 1;
		}

		LOG("[fileOpen] %s %s\n", file, mode);
		error();
	}
	return fp;
}
void fileClose(FILE *fp)
{
	errorCase(fclose(fp)); // ? Ž¸”s
}

autoList<uchar> *readAllBytes(char *file)
{
	FILE *fp = fileOpen(file, "rb");
	int size;

	{
		__int64 size64 = getFileSizeFPSS(fp);
		errorCase((__int64)IMAX < size64); // ? ‘å‚«‚·‚¬‚éB
		size = (int)size64;
	}

	uchar *fileData = (uchar *)memAlloc_NC(size);

	if(size)
		errorCase(fread(fileData, 1, size, fp) != size); // ? read error

	fileClose(fp);
	return new autoList<uchar>(fileData, size);
}
autoList<uchar> *readAllBytes_x(char *file)
{
	autoList<uchar> *out = readAllBytes(file);
	memFree(file);
	return out;
}

// FILE ver
int readChar(FILE *fp)
{
	int chr = fgetc(fp);

	if(chr == EOF && ferror(fp))
	{
		error();
	}
	return chr;
}
char *readLine(FILE *fp, int lenmax)
{
	autoList<char> *lineBuff = new autoList<char>(128);
	char *line;
	int chr;

	for(; ; )
	{
		chr = readChar(fp);

		if(chr == '\r')
		{
			if(readChar(fp) != '\n') // ? CR-(not_LF)
			{
				// noop
			}
			break;
		}
		if(chr == '\n' || chr == EOF)
		{
			break;
		}
		if(lenmax <= lineBuff->GetCount())
		{
			break;
		}
		if(chr == '\0')
		{
			chr = '\1';
		}
		lineBuff->AddElement(chr);
	}
	lineBuff->AddElement('\0');
	line = (char *)lineBuff->UnbindBuffer();
	delete lineBuff;

	if(line[0] == '\0' && chr == EOF)
	{
		memFree(line);
		line = NULL;
	}
	return line;
}
char *neReadLine(FILE *fp)
{
	char *line = readLine(fp);
	errorCase(!line);
	return line;
}
char *nnReadLine(FILE *fp, char *defaultLine)
{
	char *line = readLine(fp);

	if(!line)
		line = strx(defaultLine);

	return line;
}
autoList<char *> *readLines(char *file)
{
	FILE *fp = fileOpen(file, "rt");
	autoList<char *> *lines = new autoList<char *>();

	for(; ; )
	{
		char *line = readLine(fp);

		if(!line)
			break;

		lines->AddElement(line);
	}
	fileClose(fp);
	return lines;
}
autoList<char *> *readLines_x(char *file)
{
	autoList<char *> *lines = readLines(file);
	memFree(file);
	return lines;
}

// fileData ver
int readChar(autoList<uchar> *fileData, int &rIndex)
{
	if(rIndex < fileData->GetCount())
	{
		return fileData->GetElement(rIndex++);
	}
	return EOF;
}
char *readLine(autoList<uchar> *fileData, int &rIndex)
{
	autoList<char> *line = new autoList<char>();

	while(rIndex < fileData->GetCount())
	{
		int chr = fileData->GetElement(rIndex++);

		if(chr == '\r')
		{
			1; // “Ç‚Ý”ò‚Î‚·B
		}
		else if(chr == '\n')
		{
			break;
		}
		else
		{
			line->AddElement(chr);
		}
	}
	if(line->GetCount() == 0 && rIndex == fileData->GetCount()) // ? “Ç‚Ýž‚ÝI—¹
	{
		delete line;
		return NULL;
	}
	line->AddElement('\0');

	char *result = line->UnbindBuffer();
	delete line;
	return result;
}
char *neReadLine(autoList<uchar> *fileData, int &rIndex)
{
	char *line = readLine(fileData, rIndex);
	errorCase(!line);
	return line;
}
char *nnReadLine(autoList<uchar> *fileData, int &rIndex, char *defaultLine)
{
	char *line = readLine(fileData, rIndex);

	if(!line)
		line = strx(defaultLine);

	return line;
}
autoList<char *> *readLines(autoList<uchar> *fileData)
{
	autoList<char *> *lines = new autoList<char *>();
	int rIndex = 0;

	for(; ; )
	{
		char *line = readLine(fileData, rIndex);

		if(!line)
			break;

		lines->AddElement(line);
	}
	return lines;
}
autoList<char *> *readLines_x(autoList<uchar> *fileData)
{
	autoList<char *> *lines = readLines(fileData);
	delete fileData;
	return lines;
}

void writeAllBytes(char *file, autoList<uchar> *fileData)
{
	FILE *fp = fileOpen(file, "wb");

	errorCase(fwrite(fileData->ElementAt(0), 1, fileData->GetCount(), fp) != fileData->GetCount()); // ? write error

	fileClose(fp);
}
void writeAllBytes_cx(char *file, autoList<uchar> *fileData)
{
	writeAllBytes(file, fileData);
	delete fileData;
}

// FILE ver
void writeChar(FILE *fp, int chr)
{
	errorCase(fputc(chr, fp) == EOF);
}
void writeToken(FILE *fp, char *line)
{
	for(char *p = line; *p; p++)
		writeChar(fp, *p);
}
void writeLine(FILE *fp, char *line)
{
	writeToken(fp, line);
	writeChar(fp, '\n');
}
void writeLine_x(FILE *fp, char *line)
{
	writeLine(fp, line);
	memFree(line);
}

// fileData ver
void writeChar(autoList<uchar> *fileData, int chr)
{
	fileData->AddElement(chr);
}
void writeToken(autoList<uchar> *fileData, char *token)
{
	for(char *p = token; *p; p++)
	{
		fileData->AddElement(*p);
	}
}
void writeLine(autoList<uchar> *fileData, char *line)
{
	writeToken(fileData, line);
	fileData->AddElement('\n');
}
void writeLine_x(autoList<uchar> *fileData, char *line)
{
	writeLine(fileData, line);
	memFree(line);
}

// FILE ver
uint64 readUI64(FILE *fp, int width)
{
	uint64 value = 0;

	for(int c = 0; c < width; c++)
	{
		value |= (uint64)readChar(fp) << c * 8;
	}
	return value;
}
uint readUI32(FILE *fp, int width)
{
	return (uint)readUI64(fp, width);
}
void writeUI64(FILE *fp, uint64 value, int width)
{
	for(int c = 0; c < width; c++)
	{
		writeChar(fp, (uchar)(value >> c * 8 & 0xff));
	}
}
void writeUI32(FILE *fp, uint value, int width)
{
	writeUI64(fp, (uint64)value, width);
}

// fileData ver
uint64 readUI64(autoList<uchar> *fileData, int &rIndex, int width)
{
	uint64 value = 0;

	for(int c = 0; c < width; c++)
	{
		value |= (uint64)fileData->GetElement(rIndex++) << c * 8;
	}
	return value;
}
uint readUI32(autoList<uchar> *fileData, int &rIndex, int width)
{
	return (uint)readUI64(fileData, rIndex, width);
}
void writeUI64(autoList<uchar> *fileData, uint64 value, int width)
{
	for(int c = 0; c < width; c++)
	{
		fileData->AddElement((uchar)(value >> c * 8 & 0xff));
	}
}
void writeUI32(autoList<uchar> *fileData, uint value, int width)
{
	writeUI64(fileData, (uint64)value, width);
}

autoList<uchar> *readBlock(FILE *fp, int width)
{
	autoList<uchar> *retBlock = new autoList<uchar>();

	for(int index = 0; index < width; index++)
	{
		retBlock->AddElement((uchar)readChar(fp));
	}
	return retBlock;
}
autoList<uchar> *readBlock(autoList<uchar> *fileData, int &rIndex, int width)
{
	autoList<uchar> *retBlock = new autoList<uchar>();

	for(int index = 0; index < width; index++)
	{
		retBlock->AddElement(fileData->RefElement(rIndex++, 0x00));
	}
	return retBlock;
}
