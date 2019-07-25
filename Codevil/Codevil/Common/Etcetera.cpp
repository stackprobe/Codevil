#include "all.h"

static autoList<uchar> *LoadFileData(autoList<uchar> *fileData)
{
	return fileData->Eject();
}
static void UnloadFileData(autoList<uchar> *fileData)
{
	delete fileData;
}

static oneObject(
	resCluster<autoList<uchar> *>,
	new resCluster<autoList<uchar> *>("Etcetera.dat", "..\\..\\Etcetera.txt", ETC_MAX, 140000000, LoadFileData, UnloadFileData),
	GetEtcRes
	);

autoList<uchar> *GetEtcFileData(int etcId) // ret: ŒÄ‚Ño‚µ‘¤‚ÅŠJ•ú‚µ‚È‚¯‚ê‚Î‚È‚ç‚È‚¢B
{
	autoList<uchar> *fileData = GetEtcRes()->GetHandle(etcId)->Eject();
	GetEtcRes()->UnloadAllHandle();
	return fileData;
}
