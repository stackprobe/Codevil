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

	__int64 frmProcMilAvgNumer = 0;
	__int64 frmProcMilAvgDenom = 0;

	int effectPerFrm = 10;
	int effectCount = 1;

	for(; ; )
	{
		if(GetPound(INP_PAUSE))
		{
			break;
		}
		if(GetPound(INP_A))
		{
			effectPerFrm--;
		}
		if(GetPound(INP_B))
		{
			effectPerFrm++;
		}
		if(GetPound(INP_C))
		{
			effectCount++;
		}
		if(GetPound(INP_D))
		{
			effectCount--;
		}
		m_range(effectPerFrm, 1, 10);
		m_range(effectCount, 1, 100);

		if(ProcFrame % effectPerFrm == 0)
		{
			for(int c = 0; c < effectCount; c++)
			{
				AddCommonEffect(Gnd.EL, 0, P_DUMMY, 400.0, 300.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, cos(ProcFrame / 100.0 + c) * 0.1, sin(ProcFrame / 100.0 + c) * 0.1);
			}
		}
		DrawWall();



		// フォントのテスト
		DrawStringByFont_XCenter(
			SCREEN_CENTER_X, 20,
			"げんかいみんちょう",
			GetFontHandle("源界明朝", 70, 6, 1, 2)
			);
		DrawStringByFont_XCenter(
			SCREEN_CENTER_X, 520,
			"りいてがき",
			GetFontHandle("りいてがき筆", 50, 6, 1, 2)
			);



		frmProcMilAvgNumer += FrameProcessingMillis;
		frmProcMilAvgDenom++;

		double frmProcMilAvg = (double)frmProcMilAvgNumer / frmProcMilAvgDenom;

		if(ProcFrame % 100 == 0)
		{
			frmProcMilAvgNumer /= 2;
			frmProcMilAvgDenom /= 2;
		}

		SetPrint();
		PE.Color = GetColor(255, 128, 0);
		Print_x(xcout(
			"FST=%I64d,LT=%I64d,FPM=%d,FPMA=%.3f(EPF=%d,EC=%d)"
			,FrameStartTime
			,LangolierTime
			,FrameProcessingMillis
			,frmProcMilAvg
			,effectPerFrm
			,effectCount
			));
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
