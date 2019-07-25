#include "all.h"

int IgnoreEscapeKey;

// ���̃t�@�C������� read only {
__int64 FrameStartTime;
__int64 LangolierTime;
__int64 LowHzTime;
double EatenByLangolierEval = 0.5;
double LowHzErrorRate = 0.0;
int ProcFrame;
int FreezeInputFrame;
int WindowIsActive;
// }

static void CheckHz(void)
{
	__int64 currTime = GetCurrTime();

	if(!ProcFrame)
	{
		LangolierTime = currTime;
		LowHzTime = currTime;
	}
	else
	{
		LangolierTime += 16; // 16.666 ��菬�����̂ŁA60Hz�Ȃ�ǂ�ǂ�����������͂��B
		LowHzTime += 17;
	}

	while(currTime < LangolierTime)
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
		m_approach(EatenByLangolierEval, 1.0, 0.9);
	}
	m_maxim(LangolierTime, currTime - 30);
	EatenByLangolierEval *= 0.99;

	if(LowHzTime < currTime)
	{
		m_maxim(LowHzTime, currTime - 10);
		m_approach(LowHzErrorRate, 1.0, 0.999);
	}
	else
	{
		m_minim(LowHzTime, currTime + 20);
		LowHzErrorRate *= 0.99;
	}

//	LOG("%I64d\n", currTime - FrameStartTime); // test

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

	if(600 < ProcFrame && (0.1 < EatenByLangolierEval || 0.1 < LowHzErrorRate)) // FPS �x��
	{
		SetPrint();
		PE.Color = GetColor(255, 255, 255);
		PE_Border(GetColor(0, 0, 255));
		Print_x(xcout("FPS TUNING EBLE=%.3f LHzER=%.3f", EatenByLangolierEval, LowHzErrorRate));
		PE_Reset();
	}

	// app > @ before draw screen

	// < app

	if(Gnd.MainScreen && CurrDrawScreenHandle == GetHandle(Gnd.MainScreen))
	{
		ChangeDrawScreen(DX_SCREEN_BACK);

		if(Gnd.RealScreenDraw_W == -1)
		{
			errorCase(DrawExtendGraph(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, GetHandle(Gnd.MainScreen), 0)); // ? ���s
		}
		else
		{
			errorCase(DrawBox(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, GetColor(0, 0, 0), 1)); // ? ���s
			errorCase(DrawExtendGraph(
				Gnd.RealScreenDraw_L,
				Gnd.RealScreenDraw_T,
				Gnd.RealScreenDraw_L + Gnd.RealScreenDraw_W,
				Gnd.RealScreenDraw_T + Gnd.RealScreenDraw_H, GetHandle(Gnd.MainScreen), 0)); // ? ���s
		}
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
	errorCase(IMAX < ProcFrame); // 192.9�����x�ŃJ���X�g
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
void FreezeInput(int frame) // frame: 1 == ���̃t���[���̂�, 2 == ���̃t���[���Ǝ��̃t���[�� ...
{
	errorCase(frame < 1 || IMAX < frame);
	FreezeInputFrame = frame;
}