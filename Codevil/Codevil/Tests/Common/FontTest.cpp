#include "all.h"

void FontTest_Test01(void)
{
	for(; ; )
	{
		if(GetInput(INP_A))
			break;

		DrawCurtain();

		DrawStringByFont(
			0, 200,
			"‚ ‚ ‚ ",
			GetFontHandle("‚è‚¢‚Ä‚ª‚«•M", 100)
			);

		DrawStringByFont(
			0, 0,
			"cerulean.charlotte",
			GetFontHandle("‚è‚¢‚Ä‚ª‚«•M", 40, 6, 1, 10, 1),
			0,
			GetColor(255, 255, 255),
			GetColor(0, 20, 40)
			);

		EachFrame();
	}
}
void FontTest_Test02(void)
{
	for(; ; )
	{
		if(GetInput(INP_A))
			break;

		DrawCurtain();

		DrawStringByFont(
			10, 10,
			"b’è¬ˆ«–‚",
			GetFontHandle("Œ¹ŠE–¾’©", 70, 6, 1, 2),
			0,
			GetColor(0, 0, 0),
			GetColor(255, 255, 255)
			);

		DrawStringByFont(
			10, 150,
			"game start",
			GetFontHandle("‚è‚¢‚Ä‚ª‚«•M", 50, 6, 1, 2),
			0,
			GetColor(0, 255, 0),
			GetColor(255, 0, 0)
			);

		EachFrame();
	}
}
