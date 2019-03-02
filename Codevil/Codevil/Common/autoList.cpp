#include "all.h"

char *unbindBlock2Line(autoList<char> *list)
{
	list->AddElement('\0');
	return unbindBlock(list);
}
char *unbindBlock2Line_NR(autoList<char> *list)
{
	list->AddElement('\0');
	return list->UnbindBuffer();
}
