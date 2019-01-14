#include "all.h"

int isFilled(void *block, int fillValue, int size)
{
	for(int index = 0; index < size; index++)
		if(((uchar *)block)[index] != fillValue)
			return 0;

	return 1;
}
int isSame(autoList<uchar> *binData1, autoList<uchar> *binData2)
{
	if(binData1->GetCount() != binData2->GetCount())
		return 0;

	for(int index = 0; index < binData1->GetCount(); index++)
		if(binData1->GetElement(index) != binData2->GetElement(index))
			return 0;

	return 1;
}
