#include "all.h"

void FontTest_Test01(void)
{
	for(; ; )
	{
		if(GetInput(INP_A))
			break;

		DrawCurtain();

		DrawStringByFont(
			10, 10,
			"�b�菬����",
			GetFontHandle("���E����", 70, 6, 1, 2),
			0,
			GetColor(0, 0, 0),
			GetColor(255, 255, 255)
			);

		DrawStringByFont(
			10, 150,
			"game start",
			GetFontHandle("�肢�Ă����M", 50, 6, 1, 2),
			0,
			GetColor(0, 255, 0),
			GetColor(255, 0, 0)
			);

		EachFrame();
	}
}
