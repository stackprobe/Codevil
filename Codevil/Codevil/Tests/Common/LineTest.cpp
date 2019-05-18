#include "all.h"

void LineTest_Test01(void)
{
	for(; ; )
	{
		if(GetInput(INP_A))
			break;

		DrawCurtain();
		SetPrint();

		// ====

		{
			char *dir = "C:\\temp";
			char *file = "abcdef.txt";
			char *file2 = combine(dir, file);

			Print(dir);
			PrintRet();
			Print(file);
			PrintRet();
			Print(file2);
			PrintRet();
		}

		// ====

		EachFrame();
	}
}
