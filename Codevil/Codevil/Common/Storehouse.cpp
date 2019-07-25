#include "all.h"

#define CLUSTER_FILE "Storehouse.dat"
#define STOREHOUSE_DIR "..\\..\\Storehouse"

static int IsClusterMode(void)
{
	static int ret = -1;

	if(ret == -1)
		ret = accessible(CLUSTER_FILE) ? 1 : 0;

	return ret;
}
static autoList<uchar> *LoadFileData(autoList<uchar> *fileData)
{
	return fileData->Eject();
}
static void UnloadFileData(autoList<uchar> *fileData)
{
	delete fileData;
}
/*
	file:
		STOREHOUSE_DIR からの相対パスであること。余計な ".", ".." などを含まないこと。

	ret:
		呼び出し側で開放する必要がある。
		因みに、GetEtcRes()->GetHandle() は、戻り値を「開放してはならない」ので注意！
*/
autoList<uchar> *SH_LoadFile(char *file)
{
	autoList<uchar> *fileData;

	if(IsClusterMode())
	{
		static resCluster<autoList<uchar> *> *res;
		static autoList<char *> *fileList;

		if(!res)
		{
			int resCount;

			{
				FILE *fp = fileOpen(CLUSTER_FILE, "rb");
				resCount = readUI32(fp);
				fileClose(fp);
			}

			res = new resCluster<autoList<uchar> *>(CLUSTER_FILE, "*Dummy", resCount, 150000000, LoadFileData, UnloadFileData);
			fileList = readLines(res->GetHandle(0));

			errorCase(fileList->GetCount() != resCount - 1);
		}
		int index;

		for(index = 0; index < fileList->GetCount(); index++)
			if(!_stricmp(file, fileList->GetElement(index)))
				break;

		errorCase(index == fileList->GetCount());

		fileData = res->GetHandle(index + 1)->Eject();
		res->UnloadAllHandle();
	}
	else
	{
		file = combine(STOREHOUSE_DIR, file);
		fileData = readAllBytes(file);
		memFree(file);
	}
	return fileData;
}
void SH_SaveFile(char *file, autoList<uchar> *fileData) // file: STOREHOUSE_DIR からの相対パスであること。
{
	if(IsClusterMode())
	{
		error();
	}
	else
	{
		file = combine(STOREHOUSE_DIR, file);
		writeAllBytes(file, fileData);
		memFree(file);
	}
}
int SH_IsClusterMode(void)
{
	return IsClusterMode();
}
