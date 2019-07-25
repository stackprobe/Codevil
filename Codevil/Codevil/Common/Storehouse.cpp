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
autoList<uchar> *SH_LoadFile(char *relFile)
{
	if(IsClusterMode())
	{
		static resCluster<autoList<uchar> *> *res;

		if(!res)
		{
			FILE *fp = fileOpen(CLUSTER_FILE, "rb");
			int resCount = readUI32(fp);
			errorCase(!m_isRange(resCount, 1, IMAX));
			fileClose(fp);

			res = new resCluster<autoList<uchar> *>(CLUSTER_FILE, NULL, resCount, 150000000, LoadFileData, UnloadFileData);
		}

		// TODO
	}

	// TODO

	return NULL; // TODO
}
void SH_SaveFile(char *relFile, autoList<uchar> *fileData)
{
	// TODO
}
