#include "all.h"

// app > @ Conf_

/*
	-1 == �f�t�H���g
	0  == �ŏ��̃��j�^
	1  == 2�Ԗڂ̃��j�^
	2  == 3�Ԗڂ̃��j�^
	...
*/
int Conf_DisplayIndex = 1;

// < app

void ImportConfig(void)
{
	char *confFile = "Config.conf";

	if(accessible(confFile))
	{
		autoList<uchar> *fileData = readFile(confFile);
		int rIndex = 0;

		// app > @ LOAD Conf_

		Conf_DisplayIndex = atoi_x(neReadCfgLine(fileData, rIndex));

		// < app

		{
			char *line = neReadCfgLine(fileData, rIndex);

			errorCase(strcmp(line, "\\e"));
			memFree(line);
		}
	}
}
char *neReadCfgLine(autoList<uchar> *fileData, int &rIndex)
{
	for(; ; )
	{
		char *line = neReadLine(fileData, rIndex);

		if(*line && *line != ';')
			return line;

		memFree(line);
	}
}
