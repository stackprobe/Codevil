#include "all.h"

static void DrawWall(void)
{
	DrawCurtain();
	DrawRect(P_WHITEBOX, 100, 100, SCREEN_W - 200, SCREEN_H - 200);
}
void GameMain(void)
{
	SetCurtain();
	FreezeInput();

	MusicPlay(MUS_TITLE);

	for(; ; )
	{
		if(GetPound(INP_PAUSE))
		{
			break;
		}

		if(ProcFrame % 10 == 0)
			AddCommonEffect(Gnd.EL, 0, P_DUMMY, 400.0, 300.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, cos(ProcFrame / 100.0) * 0.1, sin(ProcFrame / 100.0) * 0.1);

		DrawWall();
		EachFrame();
	}
	FreezeInput();
	MusicFade();
	SetCurtain(30, -1.0);

	forscene(40)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();
}
