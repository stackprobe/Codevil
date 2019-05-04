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

	MusicPlay(MUS_FIELD_01);

	for(; ; )
	{
		if(GetPound(INP_PAUSE))
		{
			break;
		}

		if(ProcFrame % 10 == 0)
			AddCommonEffect(Gnd.EL, 0, P_DUMMY, 400.0, 300.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, cos(ProcFrame / 100.0) * 0.1, sin(ProcFrame / 100.0) * 0.1);

		DrawWall();



		// フォントのテスト
		DrawStringByFont(
			10, 20,
			"げんかいみんちょう",
			GetFontHandle("源界明朝", 70, 6, 1, 2)
			);
		DrawStringByFont(
			10, 550,
			"りいてがき",
			GetFontHandle("りいてがき筆", 50, 6, 1, 2)
			);



		SetPrint();
		PE.Color = GetColor(255, 128, 0);
		Print_x(xcout("EBLE=%.3f,FST=%I64d,LT=%I64d,(FST-LT)=%I64d", EatenByLangolierEval, FrameStartTime, LangolierTime, FrameStartTime - LangolierTime));
		PE_Reset();



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

	Gnd.EL->Clear();
}
