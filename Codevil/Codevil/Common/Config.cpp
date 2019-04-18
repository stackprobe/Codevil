#include "all.h"

// 設定項目 >

/*
	-1 == デフォルト
	0  == 最初のモニタ
	1  == 2番目のモニタ
	2  == 3番目のモニタ
	...
*/
int Conf_DisplayIndex = 1;

// < 設定項目

void LoadConfig(void)
{
	char *confFile = "Config.conf";

	if(accessible(confFile))
	{
		autoList<uchar> *fileData = readAllBytes(confFile);
		int rIndex = 0;

		// 設定項目 >

		Conf_DisplayIndex = atoi_x(neReadCfgLine(fileData, rIndex));

		// < 設定項目

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
