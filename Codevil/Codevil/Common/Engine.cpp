#include "all.h"

int IgnoreEscapeKey;

// 他のファイルからは read only {
__int64 FrameStartTime;
__int64 LangolierTime;
double EatenByLangolierEval = 0.5;
int ProcFrame;
int FreezeInputFrame;
int WindowIsActive;
// }

static void CheckHz(void)
{
	__int64 currTime = GetCurrTime();

	if(!ProcFrame)
		LangolierTime = currTime;
	else
		LangolierTime += 16; // 16.666 より小さいので、60Hzならどんどん引き離されるはず。
//		LangolierTime += 17; // test
//		LangolierTime += 18; // test
//		LangolierTime += 19; // test

	if(currTime < LangolierTime)
	{
		m_approach(EatenByLangolierEval, 1.0, 0.9);

		do
		{
			Sleep(1);

			// DxLib >

			ScreenFlip();

			if(ProcessMessage() == -1)
			{
				EndProc();
			}

			// < DxLib

			currTime = GetCurrTime();
		}
		while(currTime < LangolierTime);
	}
	else
		EatenByLangolierEval *= 0.99;

	FrameStartTime = currTime;
}

void EachFrame(void)
{
	if(!SEEachFrame())
	{
		MusicEachFrame();
	}
	Gnd.EL->ExecuteAllTask();
	CurtainEachFrame();

	if(900 < ProcFrame && 0.1 < EatenByLangolierEval) // 暫定 暫定 暫定 暫定 暫定
	{
		static int passedCount = 900;

		if(m_countDown(passedCount))
		{
			DPE_SetBright(GetColor(128, 0, 0));
			DPE_SetAlpha(0.5);
			DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, 16);
			DPE_Reset();

			SetPrint();
			PE.Color = GetColor(255, 255, 0);
			Print_x(xcout("V-SYNC ALERT / EBLE=%.3f FST=%I64d LT=%I64d (%d)", EatenByLangolierEval, FrameStartTime, LangolierTime, passedCount));
			PE_Reset();
		}
	}

	// app > @ before draw screen

	// < app

	if(Gnd.MainScreen && CurrDrawScreenHandle == GetHandle(Gnd.MainScreen))
	{
		ChangeDrawScreen(DX_SCREEN_BACK);

		// app > @ draw screen

		if(Gnd.RealScreenDraw_W == -1)
		{
			errorCase(DrawExtendGraph(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, GetHandle(Gnd.MainScreen), 0)); // ? 失敗
		}
		else
		{
			errorCase(DrawBox(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, GetColor(0, 0, 0), 1)); // ? 失敗
			errorCase(DrawExtendGraph(
				Gnd.RealScreenDraw_L,
				Gnd.RealScreenDraw_T,
				Gnd.RealScreenDraw_L + Gnd.RealScreenDraw_W,
				Gnd.RealScreenDraw_T + Gnd.RealScreenDraw_H, GetHandle(Gnd.MainScreen), 0)); // ? 失敗
		}

		// < app
	}

	// app > @ post draw screen

	// < app

	// DxLib >

	ScreenFlip();

	if(!IgnoreEscapeKey && CheckHitKey(KEY_INPUT_ESCAPE) == 1 || ProcessMessage() == -1)
	{
		EndProc();
	}

	// < DxLib

	CheckHz();

	ProcFrame++;
	errorCase(IMAX < ProcFrame); // 192.9日程度でカンスト
	m_countDown(FreezeInputFrame);
	WindowIsActive = IsWindowActive();

	PadEachFrame();
	KeyEachFrame();
	InputEachFrame();
	MouseEachFrame();

	if(Gnd.RealScreen_W != SCREEN_W || Gnd.RealScreen_H != SCREEN_H)
	{
		if(!Gnd.MainScreen)
			Gnd.MainScreen = CreateSubScreen(SCREEN_W, SCREEN_H);

		ChangeDrawScreen(Gnd.MainScreen);
	}
}
void FreezeInput(int frame) // frame: 1 == このフレームのみ, 2 == このフレームと次のフレーム ...
{
	errorCase(frame < 1 || IMAX < frame);
	FreezeInputFrame = frame;
}
