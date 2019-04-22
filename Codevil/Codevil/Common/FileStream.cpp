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

	if(!fp) // ? 失敗
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
	errorCase(fclose(fp)); // ? 失敗
}

int readChar(FILE *fp) // バイナリ・テキスト問わずストリームから１バイト(１文字)読み込む。
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
				error();
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
	line = unbindBlock2Line(lineBuff);

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

void writeChar(FILE *fp, int chr) // バイナリ・テキスト問わずストリームに１バイト(１文字)書き出す。
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
