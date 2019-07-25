#include "all.h"

void StorehouseTest_Test01(void)
{
	{
		autoList<char *> *lines = readLines_x(SH_LoadFile("Flandre.txt"));
		int index;

		LOG("Flandre.txt ---->\n");

		for(index = 0; index < lines->GetCount(); index++)
			LOG("%s\n", lines->GetElement(index));

		LOG("<----\n");

		releaseList(lines, (void (*)(char *))memFree);
	}

	{
		autoList<char *> *lines = readLines_x(SH_LoadFile("Remilia.txt"));
		int index;

		LOG("Remilia.txt ---->\n");

		for(index = 0; index < lines->GetCount(); index++)
			LOG("%s\n", lines->GetElement(index));

		LOG("<----\n");

		releaseList(lines, (void (*)(char *))memFree);
	}

	{
		autoList<uchar> *fileData = SH_LoadFile("YesNoEditable.txt");
		int rIndex = 0;
		char *line = readLine(fileData, rIndex);

		LOG("line: %s\n", line);

		char *lineNew;

		if(!strcmp(line, "Yes"))
			lineNew = "No";
		else
			lineNew = "Yes";

		LOG("lineNew: %s\n", lineNew);

		if(SH_IsClusterMode())
		{
			LOGPOS();
		}
		else
		{
			fileData->Clear();
			writeLine(fileData, lineNew);
			SH_SaveFile("YesNoEditable.txt", fileData);
		}
		delete fileData;
		memFree(line);
	}
}
