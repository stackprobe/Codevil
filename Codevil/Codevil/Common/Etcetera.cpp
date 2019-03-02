#include "all.h"

static autoList<uchar> *LoadFileData(autoList<uchar> *fileData)
{
	return fileData->Molt();
}
static void UnloadFileData(autoList<uchar> *fileData)
{
	delete fileData;
}

oneObject(
	resCluster<autoList<uchar> *>,
	new resCluster<autoList<uchar> *>("Etcetera.dat", "..\\..\\Etcetera.txt", ETC_MAX, 140000000, LoadFileData, UnloadFileData),
	GetEtcRes
	);
